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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  temp ;
struct if_spi_card {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int FIRMWARE_DNLD_OK ; 
 int HELPER_FW_LOAD_CHUNK_SZ ; 
 int /*<<< orphan*/  IF_SPI_CARD_INT_CAUSE_REG ; 
 int IF_SPI_CIC_CMD_DOWNLOAD_OVER ; 
 int /*<<< orphan*/  IF_SPI_CMD_RDWRPORT_REG ; 
 int /*<<< orphan*/  IF_SPI_HIST_CMD_DOWNLOAD_RDY ; 
 int /*<<< orphan*/  IF_SPI_HOST_INT_STATUS_REG ; 
 int /*<<< orphan*/  IF_SPI_SCRATCH_1_REG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int spu_set_interrupt_mode (struct if_spi_card*,int,int /*<<< orphan*/ ) ; 
 int spu_wait_for_u16 (struct if_spi_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spu_write (struct if_spi_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int spu_write_u16 (struct if_spi_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int if_spi_prog_helper_firmware(struct if_spi_card *card,
					const struct firmware *firmware)
{
	int err = 0;
	int bytes_remaining;
	const u8 *fw;
	u8 temp[HELPER_FW_LOAD_CHUNK_SZ];

	err = spu_set_interrupt_mode(card, 1, 0);
	if (err)
		goto out;

	bytes_remaining = firmware->size;
	fw = firmware->data;

	/* Load helper firmware image */
	while (bytes_remaining > 0) {
		/*
		 * Scratch pad 1 should contain the number of bytes we
		 * want to download to the firmware
		 */
		err = spu_write_u16(card, IF_SPI_SCRATCH_1_REG,
					HELPER_FW_LOAD_CHUNK_SZ);
		if (err)
			goto out;

		err = spu_wait_for_u16(card, IF_SPI_HOST_INT_STATUS_REG,
					IF_SPI_HIST_CMD_DOWNLOAD_RDY,
					IF_SPI_HIST_CMD_DOWNLOAD_RDY);
		if (err)
			goto out;

		/*
		 * Feed the data into the command read/write port reg
		 * in chunks of 64 bytes
		 */
		memset(temp, 0, sizeof(temp));
		memcpy(temp, fw,
		       min(bytes_remaining, HELPER_FW_LOAD_CHUNK_SZ));
		mdelay(10);
		err = spu_write(card, IF_SPI_CMD_RDWRPORT_REG,
					temp, HELPER_FW_LOAD_CHUNK_SZ);
		if (err)
			goto out;

		/* Interrupt the boot code */
		err = spu_write_u16(card, IF_SPI_HOST_INT_STATUS_REG, 0);
		if (err)
			goto out;
		err = spu_write_u16(card, IF_SPI_CARD_INT_CAUSE_REG,
				       IF_SPI_CIC_CMD_DOWNLOAD_OVER);
		if (err)
			goto out;
		bytes_remaining -= HELPER_FW_LOAD_CHUNK_SZ;
		fw += HELPER_FW_LOAD_CHUNK_SZ;
	}

	/*
	 * Once the helper / single stage firmware download is complete,
	 * write 0 to scratch pad 1 and interrupt the
	 * bootloader. This completes the helper download.
	 */
	err = spu_write_u16(card, IF_SPI_SCRATCH_1_REG, FIRMWARE_DNLD_OK);
	if (err)
		goto out;
	err = spu_write_u16(card, IF_SPI_HOST_INT_STATUS_REG, 0);
	if (err)
		goto out;
	err = spu_write_u16(card, IF_SPI_CARD_INT_CAUSE_REG,
				IF_SPI_CIC_CMD_DOWNLOAD_OVER);
out:
	if (err)
		pr_err("failed to load helper firmware (err=%d)\n", err);

	return err;
}