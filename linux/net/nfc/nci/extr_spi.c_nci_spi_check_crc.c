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
typedef  scalar_t__ u16 ;
struct sk_buff {int* data; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_INIT ; 
 scalar_t__ NCI_SPI_CRC_LEN ; 
 scalar_t__ crc_ccitt (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int nci_spi_check_crc(struct sk_buff *skb)
{
	u16 crc_data = (skb->data[skb->len - 2] << 8) |
			skb->data[skb->len - 1];
	int ret;

	ret = (crc_ccitt(CRC_INIT, skb->data, skb->len - NCI_SPI_CRC_LEN)
			== crc_data);

	skb_trim(skb, skb->len - NCI_SPI_CRC_LEN);

	return ret;
}