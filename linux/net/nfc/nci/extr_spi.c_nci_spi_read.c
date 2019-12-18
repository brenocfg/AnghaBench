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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nci_spi {scalar_t__ acknowledge_mode; int /*<<< orphan*/  req_completion; int /*<<< orphan*/  req_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACKNOWLEDGE_ACK ; 
 int /*<<< orphan*/  ACKNOWLEDGE_NACK ; 
 scalar_t__ NCI_SPI_CRC_ENABLED ; 
 struct sk_buff* __nci_spi_read (struct nci_spi*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_spi_check_crc (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_spi_get_ack (struct sk_buff*) ; 
 int /*<<< orphan*/  send_acknowledge (struct nci_spi*,int /*<<< orphan*/ ) ; 

struct sk_buff *nci_spi_read(struct nci_spi *nspi)
{
	struct sk_buff *skb;

	/* Retrieve frame from SPI */
	skb = __nci_spi_read(nspi);
	if (!skb)
		goto done;

	if (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) {
		if (!nci_spi_check_crc(skb)) {
			send_acknowledge(nspi, ACKNOWLEDGE_NACK);
			goto done;
		}

		/* In case of acknowledged mode: if ACK or NACK received,
		 * unblock completion of latest frame sent.
		 */
		nspi->req_result = nci_spi_get_ack(skb);
		if (nspi->req_result)
			complete(&nspi->req_completion);
	}

	/* If there is no payload (ACK/NACK only frame),
	 * free the socket buffer
	 */
	if (!skb->len) {
		kfree_skb(skb);
		skb = NULL;
		goto done;
	}

	if (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED)
		send_acknowledge(nspi, ACKNOWLEDGE_ACK);

done:

	return skb;
}