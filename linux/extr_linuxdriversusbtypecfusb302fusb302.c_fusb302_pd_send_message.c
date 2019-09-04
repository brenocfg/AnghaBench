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
typedef  size_t u8 ;
struct pd_message {int header; int* payload; } ;
struct fusb302_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t FUSB302_TKN_EOP ; 
 size_t FUSB302_TKN_JAMCRC ; 
 int FUSB302_TKN_PACKSYM ; 
 size_t FUSB302_TKN_SYNC1 ; 
 size_t FUSB302_TKN_SYNC2 ; 
 size_t FUSB302_TKN_TXOFF ; 
 size_t FUSB302_TKN_TXON ; 
 int /*<<< orphan*/  FUSB_REG_FIFOS ; 
 int fusb302_i2c_block_write (struct fusb302_chip*,int /*<<< orphan*/ ,size_t,size_t*) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,int*,int) ; 
 int pd_header_cnt_le (int) ; 

__attribute__((used)) static int fusb302_pd_send_message(struct fusb302_chip *chip,
				   const struct pd_message *msg)
{
	int ret = 0;
	u8 buf[40];
	u8 pos = 0;
	int len;

	/* SOP tokens */
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC2;

	len = pd_header_cnt_le(msg->header) * 4;
	/* plug 2 for header */
	len += 2;
	if (len > 0x1F) {
		fusb302_log(chip,
			    "PD message too long %d (incl. header)", len);
		return -EINVAL;
	}
	/* packsym tells the FUSB302 chip that the next X bytes are payload */
	buf[pos++] = FUSB302_TKN_PACKSYM | (len & 0x1F);
	memcpy(&buf[pos], &msg->header, sizeof(msg->header));
	pos += sizeof(msg->header);

	len -= 2;
	memcpy(&buf[pos], msg->payload, len);
	pos += len;

	/* CRC */
	buf[pos++] = FUSB302_TKN_JAMCRC;
	/* EOP */
	buf[pos++] = FUSB302_TKN_EOP;
	/* turn tx off after sending message */
	buf[pos++] = FUSB302_TKN_TXOFF;
	/* start transmission */
	buf[pos++] = FUSB302_TKN_TXON;

	ret = fusb302_i2c_block_write(chip, FUSB_REG_FIFOS, pos, buf);
	if (ret < 0)
		return ret;
	fusb302_log(chip, "sending PD message header: %x", msg->header);
	fusb302_log(chip, "sending PD message len: %d", len);

	return ret;
}