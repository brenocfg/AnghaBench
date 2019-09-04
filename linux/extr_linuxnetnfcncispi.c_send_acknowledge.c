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
typedef  unsigned char u8 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nci_spi {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_INIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char NCI_SPI_ACK_SHIFT ; 
 unsigned char NCI_SPI_CRC_ENABLED ; 
 unsigned char NCI_SPI_DIRECT_WRITE ; 
 int /*<<< orphan*/  NCI_SPI_HDR_LEN ; 
 int __nci_spi_send (struct nci_spi*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int crc_ccitt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nci_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static int send_acknowledge(struct nci_spi *nspi, u8 acknowledge)
{
	struct sk_buff *skb;
	unsigned char *hdr;
	u16 crc;
	int ret;

	skb = nci_skb_alloc(nspi->ndev, 0, GFP_KERNEL);

	/* add the NCI SPI header to the start of the buffer */
	hdr = skb_push(skb, NCI_SPI_HDR_LEN);
	hdr[0] = NCI_SPI_DIRECT_WRITE;
	hdr[1] = NCI_SPI_CRC_ENABLED;
	hdr[2] = acknowledge << NCI_SPI_ACK_SHIFT;
	hdr[3] = 0;

	crc = crc_ccitt(CRC_INIT, skb->data, skb->len);
	skb_put_u8(skb, crc >> 8);
	skb_put_u8(skb, crc & 0xFF);

	ret = __nci_spi_send(nspi, skb, 0);

	kfree_skb(skb);

	return ret;
}