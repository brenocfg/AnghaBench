#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sdio_func {int dummy; } ;
struct if_sdio_card {TYPE_1__* priv; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int is_activity_detected; } ;

/* Variables and functions */
 int IF_SDIO_H_INT_DNLD ; 
 int /*<<< orphan*/  IF_SDIO_H_INT_STATUS ; 
 int IF_SDIO_H_INT_UPLD ; 
 int if_sdio_card_to_host (struct if_sdio_card*) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,unsigned int) ; 
 int /*<<< orphan*/  lbs_host_to_card_done (TYPE_1__*) ; 
 struct if_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void if_sdio_interrupt(struct sdio_func *func)
{
	int ret;
	struct if_sdio_card *card;
	u8 cause;

	card = sdio_get_drvdata(func);

	cause = sdio_readb(card->func, IF_SDIO_H_INT_STATUS, &ret);
	if (ret || !cause)
		return;

	lbs_deb_sdio("interrupt: 0x%X\n", (unsigned)cause);

	sdio_writeb(card->func, ~cause, IF_SDIO_H_INT_STATUS, &ret);
	if (ret)
		return;

	/*
	 * Ignore the define name, this really means the card has
	 * successfully received the command.
	 */
	card->priv->is_activity_detected = 1;
	if (cause & IF_SDIO_H_INT_DNLD)
		lbs_host_to_card_done(card->priv);


	if (cause & IF_SDIO_H_INT_UPLD) {
		ret = if_sdio_card_to_host(card);
		if (ret)
			return;
	}
}