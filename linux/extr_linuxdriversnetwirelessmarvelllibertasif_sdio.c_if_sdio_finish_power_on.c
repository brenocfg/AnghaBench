#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct lbs_private {int fw_ready; int /*<<< orphan*/  dev; } ;
struct if_sdio_card {scalar_t__ model; int started; int /*<<< orphan*/  pwron_waitq; scalar_t__ rx_unit; struct sdio_func* func; struct lbs_private* priv; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FUNC_INIT ; 
 int /*<<< orphan*/  IF_SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  IF_SDIO_H_INT_MASK ; 
 scalar_t__ MODEL_8385 ; 
 scalar_t__ MODEL_8686 ; 
 scalar_t__ MODEL_8688 ; 
 scalar_t__ __lbs_cmd (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  if_sdio_interrupt ; 
 int /*<<< orphan*/  if_sdio_power_off (struct if_sdio_card*) ; 
 scalar_t__ if_sdio_read_rx_unit (struct if_sdio_card*) ; 
 int /*<<< orphan*/  lbs_cmd_copyback ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*) ; 
 int lbs_start_card (struct lbs_private*) ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_alert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_sdio_finish_power_on(struct if_sdio_card *card)
{
	struct sdio_func *func = card->func;
	struct lbs_private *priv = card->priv;
	int ret;

	sdio_claim_host(func);
	sdio_set_block_size(card->func, IF_SDIO_BLOCK_SIZE);

	/*
	 * Get rx_unit if the chip is SD8688 or newer.
	 * SD8385 & SD8686 do not have rx_unit.
	 */
	if ((card->model != MODEL_8385)
			&& (card->model != MODEL_8686))
		card->rx_unit = if_sdio_read_rx_unit(card);
	else
		card->rx_unit = 0;

	/*
	 * Set up the interrupt handler late.
	 *
	 * If we set it up earlier, the (buggy) hardware generates a spurious
	 * interrupt, even before the interrupt has been enabled, with
	 * CCCR_INTx = 0.
	 *
	 * We register the interrupt handler late so that we can handle any
	 * spurious interrupts, and also to avoid generation of that known
	 * spurious interrupt in the first place.
	 */
	ret = sdio_claim_irq(func, if_sdio_interrupt);
	if (ret)
		goto release;

	/*
	 * Enable interrupts now that everything is set up
	 */
	sdio_writeb(func, 0x0f, IF_SDIO_H_INT_MASK, &ret);
	if (ret)
		goto release_irq;

	sdio_release_host(func);

	/* Set fw_ready before queuing any commands so that
	 * lbs_thread won't block from sending them to firmware.
	 */
	priv->fw_ready = 1;

	/*
	 * FUNC_INIT is required for SD8688 WLAN/BT multiple functions
	 */
	if (card->model == MODEL_8688) {
		struct cmd_header cmd;

		memset(&cmd, 0, sizeof(cmd));

		lbs_deb_sdio("send function INIT command\n");
		if (__lbs_cmd(priv, CMD_FUNC_INIT, &cmd, sizeof(cmd),
				lbs_cmd_copyback, (unsigned long) &cmd))
			netdev_alert(priv->dev, "CMD_FUNC_INIT cmd failed\n");
	}

	wake_up(&card->pwron_waitq);

	if (!card->started) {
		ret = lbs_start_card(priv);
		if_sdio_power_off(card);
		if (ret == 0) {
			card->started = true;
			/* Tell PM core that we don't need the card to be
			 * powered now */
			pm_runtime_put(&func->dev);
		}
	}

	return;

release_irq:
	sdio_release_irq(func);
release:
	sdio_release_host(func);
}