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
typedef  int u16 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct nci_spi {unsigned char acknowledge_mode; scalar_t__ req_result; int /*<<< orphan*/  req_completion; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACKNOWLEDGE_NACK ; 
 int /*<<< orphan*/  CRC_INIT ; 
 int EIO ; 
 int ETIME ; 
 unsigned char NCI_SPI_CRC_DISABLED ; 
 unsigned char NCI_SPI_CRC_ENABLED ; 
 unsigned char NCI_SPI_DIRECT_WRITE ; 
 int /*<<< orphan*/  NCI_SPI_HDR_LEN ; 
 int /*<<< orphan*/  NCI_SPI_SEND_TIMEOUT ; 
 int __nci_spi_send (struct nci_spi*,struct sk_buff*,int) ; 
 int crc_ccitt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

int nci_spi_send(struct nci_spi *nspi,
		 struct completion *write_handshake_completion,
		 struct sk_buff *skb)
{
	unsigned int payload_len = skb->len;
	unsigned char *hdr;
	int ret;
	long completion_rc;

	/* add the NCI SPI header to the start of the buffer */
	hdr = skb_push(skb, NCI_SPI_HDR_LEN);
	hdr[0] = NCI_SPI_DIRECT_WRITE;
	hdr[1] = nspi->acknowledge_mode;
	hdr[2] = payload_len >> 8;
	hdr[3] = payload_len & 0xFF;

	if (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) {
		u16 crc;

		crc = crc_ccitt(CRC_INIT, skb->data, skb->len);
		skb_put_u8(skb, crc >> 8);
		skb_put_u8(skb, crc & 0xFF);
	}

	if (write_handshake_completion)	{
		/* Trick SPI driver to raise chip select */
		ret = __nci_spi_send(nspi, NULL, 1);
		if (ret)
			goto done;

		/* wait for NFC chip hardware handshake to complete */
		if (wait_for_completion_timeout(write_handshake_completion,
						msecs_to_jiffies(1000)) == 0) {
			ret = -ETIME;
			goto done;
		}
	}

	ret = __nci_spi_send(nspi, skb, 0);
	if (ret != 0 || nspi->acknowledge_mode == NCI_SPI_CRC_DISABLED)
		goto done;

	reinit_completion(&nspi->req_completion);
	completion_rc =	wait_for_completion_interruptible_timeout(
							&nspi->req_completion,
							NCI_SPI_SEND_TIMEOUT);

	if (completion_rc <= 0 || nspi->req_result == ACKNOWLEDGE_NACK)
		ret = -EIO;

done:
	kfree_skb(skb);

	return ret;
}