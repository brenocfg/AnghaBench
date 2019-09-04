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
struct pd_message {int header; scalar_t__ payload; } ;
struct fusb302_chip {int /*<<< orphan*/  tcpm_port; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FUSB_REG_FIFOS ; 
 scalar_t__ PD_CTRL_GOOD_CRC ; 
 int PD_MAX_PAYLOAD ; 
 int /*<<< orphan*/  TCPC_TX_SUCCESS ; 
 int fusb302_i2c_block_read (struct fusb302_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,int) ; 
 int pd_header_cnt_le (int) ; 
 scalar_t__ pd_header_type_le (int) ; 
 int /*<<< orphan*/  tcpm_pd_receive (int /*<<< orphan*/ ,struct pd_message*) ; 
 int /*<<< orphan*/  tcpm_pd_transmit_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_pd_read_message(struct fusb302_chip *chip,
				   struct pd_message *msg)
{
	int ret = 0;
	u8 token;
	u8 crc[4];
	int len;

	/* first SOP token */
	ret = fusb302_i2c_read(chip, FUSB_REG_FIFOS, &token);
	if (ret < 0)
		return ret;
	ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, 2,
				     (u8 *)&msg->header);
	if (ret < 0)
		return ret;
	len = pd_header_cnt_le(msg->header) * 4;
	/* add 4 to length to include the CRC */
	if (len > PD_MAX_PAYLOAD * 4) {
		fusb302_log(chip, "PD message too long %d", len);
		return -EINVAL;
	}
	if (len > 0) {
		ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, len,
					     (u8 *)msg->payload);
		if (ret < 0)
			return ret;
	}
	/* another 4 bytes to read CRC out */
	ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, 4, crc);
	if (ret < 0)
		return ret;
	fusb302_log(chip, "PD message header: %x", msg->header);
	fusb302_log(chip, "PD message len: %d", len);

	/*
	 * Check if we've read off a GoodCRC message. If so then indicate to
	 * TCPM that the previous transmission has completed. Otherwise we pass
	 * the received message over to TCPM for processing.
	 *
	 * We make this check here instead of basing the reporting decision on
	 * the IRQ event type, as it's possible for the chip to report the
	 * TX_SUCCESS and GCRCSENT events out of order on occasion, so we need
	 * to check the message type to ensure correct reporting to TCPM.
	 */
	if ((!len) && (pd_header_type_le(msg->header) == PD_CTRL_GOOD_CRC))
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	else
		tcpm_pd_receive(chip->tcpm_port, msg);

	return ret;
}