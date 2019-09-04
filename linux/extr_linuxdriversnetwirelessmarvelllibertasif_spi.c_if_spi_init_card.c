#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct lbs_private {int /*<<< orphan*/  dev; } ;
struct if_spi_card {scalar_t__ card_id; TYPE_3__* spi; int /*<<< orphan*/  card_rev; TYPE_1__* pdata; struct lbs_private* priv; } ;
struct firmware {int dummy; } ;
struct TYPE_10__ {scalar_t__ model; } ;
struct TYPE_9__ {int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  chip_select; TYPE_2__* master; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  bus_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  use_dummy_writes; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  IF_SPI_SCRATCH_4_REG ; 
 scalar_t__ SUCCESSFUL_FW_DOWNLOAD_MAGIC ; 
 TYPE_4__* fw_table ; 
 int if_spi_prog_helper_firmware (struct if_spi_card*,struct firmware const*) ; 
 int if_spi_prog_main_firmware (struct if_spi_card*,struct firmware const*) ; 
 int /*<<< orphan*/  lbs_deb_spi (char*,...) ; 
 int lbs_get_firmware (int /*<<< orphan*/ *,int,TYPE_4__*,struct firmware const**,struct firmware const**) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int spu_get_chip_revision (struct if_spi_card*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int spu_init (struct if_spi_card*,int /*<<< orphan*/ ) ; 
 int spu_read_u32 (struct if_spi_card*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int spu_set_interrupt_mode (struct if_spi_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int if_spi_init_card(struct if_spi_card *card)
{
	struct lbs_private *priv = card->priv;
	int err, i;
	u32 scratch;
	const struct firmware *helper = NULL;
	const struct firmware *mainfw = NULL;

	err = spu_init(card, card->pdata->use_dummy_writes);
	if (err)
		goto out;
	err = spu_get_chip_revision(card, &card->card_id, &card->card_rev);
	if (err)
		goto out;

	err = spu_read_u32(card, IF_SPI_SCRATCH_4_REG, &scratch);
	if (err)
		goto out;
	if (scratch == SUCCESSFUL_FW_DOWNLOAD_MAGIC)
		lbs_deb_spi("Firmware is already loaded for "
			    "Marvell WLAN 802.11 adapter\n");
	else {
		/* Check if we support this card */
		for (i = 0; i < ARRAY_SIZE(fw_table); i++) {
			if (card->card_id == fw_table[i].model)
				break;
		}
		if (i == ARRAY_SIZE(fw_table)) {
			netdev_err(priv->dev, "Unsupported chip_id: 0x%02x\n",
				   card->card_id);
			err = -ENODEV;
			goto out;
		}

		err = lbs_get_firmware(&card->spi->dev, card->card_id,
					&fw_table[0], &helper, &mainfw);
		if (err) {
			netdev_err(priv->dev, "failed to find firmware (%d)\n",
				   err);
			goto out;
		}

		lbs_deb_spi("Initializing FW for Marvell WLAN 802.11 adapter "
				"(chip_id = 0x%04x, chip_rev = 0x%02x) "
				"attached to SPI bus_num %d, chip_select %d. "
				"spi->max_speed_hz=%d\n",
				card->card_id, card->card_rev,
				card->spi->master->bus_num,
				card->spi->chip_select,
				card->spi->max_speed_hz);
		err = if_spi_prog_helper_firmware(card, helper);
		if (err)
			goto out;
		err = if_spi_prog_main_firmware(card, mainfw);
		if (err)
			goto out;
		lbs_deb_spi("loaded FW for Marvell WLAN 802.11 adapter\n");
	}

	err = spu_set_interrupt_mode(card, 0, 1);
	if (err)
		goto out;

out:
	return err;
}