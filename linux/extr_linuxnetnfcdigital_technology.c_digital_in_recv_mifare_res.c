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
struct sk_buff {int len; scalar_t__* data; } ;

/* Variables and functions */
 int DIGITAL_CRC_LEN ; 
 scalar_t__ DIGITAL_MIFARE_ACK_RES ; 
 int DIGITAL_MIFARE_READ_RES_LEN ; 
 int EIO ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 scalar_t__ digital_skb_check_crc_a (struct sk_buff*) ; 

int digital_in_recv_mifare_res(struct sk_buff *resp)
{
	/* Successful READ command response is 16 data bytes + 2 CRC bytes long.
	 * Since the driver can't differentiate a ACK/NACK response from a valid
	 * READ response, the CRC calculation must be handled at digital level
	 * even if the driver supports it for this technology.
	 */
	if (resp->len == DIGITAL_MIFARE_READ_RES_LEN + DIGITAL_CRC_LEN) {
		if (digital_skb_check_crc_a(resp)) {
			PROTOCOL_ERR("9.4.1.2");
			return -EIO;
		}

		return 0;
	}

	/* ACK response (i.e. successful WRITE). */
	if (resp->len == 1 && resp->data[0] == DIGITAL_MIFARE_ACK_RES) {
		resp->data[0] = 0;
		return 0;
	}

	/* NACK and any other responses are treated as error. */
	return -EIO;
}