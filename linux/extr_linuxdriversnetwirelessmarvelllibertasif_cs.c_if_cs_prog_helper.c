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
typedef  int u8 ;
struct if_cs_card {scalar_t__ align_regs; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODEV ; 
 int IF_CS_BIT_COMMAND ; 
 int /*<<< orphan*/  IF_CS_CARD_STATUS ; 
 int /*<<< orphan*/  IF_CS_CMD ; 
 int /*<<< orphan*/  IF_CS_CMD_LEN ; 
 int /*<<< orphan*/  IF_CS_HOST_INT_CAUSE ; 
 int /*<<< orphan*/  IF_CS_HOST_STATUS ; 
 int /*<<< orphan*/  IF_CS_SCRATCH ; 
 int IF_CS_SCRATCH_BOOT_OK ; 
 int IF_CS_SCRATCH_HELPER_OK ; 
 int if_cs_poll_while_fw_download (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int if_cs_read16 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int if_cs_read8 (struct if_cs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_cs_write16_rep (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_cs_write8 (struct if_cs_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_deb_cs (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static int if_cs_prog_helper(struct if_cs_card *card, const struct firmware *fw)
{
	int ret = 0;
	int sent = 0;
	u8  scratch;

	/*
	 * This is the only place where an unaligned register access happens on
	 * the CF8305 card, therefore for the sake of speed of the driver, we do
	 * the alignment correction here.
	 */
	if (card->align_regs)
		scratch = if_cs_read16(card, IF_CS_SCRATCH) >> 8;
	else
		scratch = if_cs_read8(card, IF_CS_SCRATCH);

	/* "If the value is 0x5a, the firmware is already
	 * downloaded successfully"
	 */
	if (scratch == IF_CS_SCRATCH_HELPER_OK)
		goto done;

	/* "If the value is != 00, it is invalid value of register */
	if (scratch != IF_CS_SCRATCH_BOOT_OK) {
		ret = -ENODEV;
		goto done;
	}

	lbs_deb_cs("helper size %td\n", fw->size);

	/* "Set the 5 bytes of the helper image to 0" */
	/* Not needed, this contains an ARM branch instruction */

	for (;;) {
		/* "the number of bytes to send is 256" */
		int count = 256;
		int remain = fw->size - sent;

		if (remain < count)
			count = remain;

		/*
		 * "write the number of bytes to be sent to the I/O Command
		 * write length register"
		 */
		if_cs_write16(card, IF_CS_CMD_LEN, count);

		/* "write this to I/O Command port register as 16 bit writes */
		if (count)
			if_cs_write16_rep(card, IF_CS_CMD,
				&fw->data[sent],
				count >> 1);

		/*
		 * "Assert the download over interrupt command in the Host
		 * status register"
		 */
		if_cs_write8(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);

		/*
		 * "Assert the download over interrupt command in the Card
		 * interrupt case register"
		 */
		if_cs_write16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);

		/*
		 * "The host polls the Card Status register ... for 50 ms before
		 * declaring a failure"
		 */
		ret = if_cs_poll_while_fw_download(card, IF_CS_CARD_STATUS,
			IF_CS_BIT_COMMAND);
		if (ret < 0) {
			pr_err("can't download helper at 0x%x, ret %d\n",
			       sent, ret);
			goto done;
		}

		if (count == 0)
			break;

		sent += count;
	}

done:
	return ret;
}