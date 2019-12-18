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
struct spi_transfer {unsigned char* tx_buf; int len; int cs_change; unsigned char* rx_buf; int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  delay_usecs; } ;
struct spi_message {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nci_spi {unsigned char acknowledge_mode; int /*<<< orphan*/  spi; int /*<<< orphan*/  xfer_speed_hz; int /*<<< orphan*/  xfer_udelay; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char NCI_SPI_CRC_ENABLED ; 
 unsigned char NCI_SPI_CRC_LEN ; 
 unsigned char NCI_SPI_DIRECT_READ ; 
 unsigned char NCI_SPI_MSB_PAYLOAD_MASK ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* nci_skb_alloc (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned short) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static struct sk_buff *__nci_spi_read(struct nci_spi *nspi)
{
	struct sk_buff *skb;
	struct spi_message m;
	unsigned char req[2], resp_hdr[2];
	struct spi_transfer tx, rx;
	unsigned short rx_len = 0;
	int ret;

	spi_message_init(&m);

	memset(&tx, 0, sizeof(struct spi_transfer));
	req[0] = NCI_SPI_DIRECT_READ;
	req[1] = nspi->acknowledge_mode;
	tx.tx_buf = req;
	tx.len = 2;
	tx.cs_change = 0;
	tx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&tx, &m);

	memset(&rx, 0, sizeof(struct spi_transfer));
	rx.rx_buf = resp_hdr;
	rx.len = 2;
	rx.cs_change = 1;
	rx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&rx, &m);

	ret = spi_sync(nspi->spi, &m);
	if (ret)
		return NULL;

	if (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED)
		rx_len = ((resp_hdr[0] & NCI_SPI_MSB_PAYLOAD_MASK) << 8) +
				resp_hdr[1] + NCI_SPI_CRC_LEN;
	else
		rx_len = (resp_hdr[0] << 8) | resp_hdr[1];

	skb = nci_skb_alloc(nspi->ndev, rx_len, GFP_KERNEL);
	if (!skb)
		return NULL;

	spi_message_init(&m);

	memset(&rx, 0, sizeof(struct spi_transfer));
	rx.rx_buf = skb_put(skb, rx_len);
	rx.len = rx_len;
	rx.cs_change = 0;
	rx.delay_usecs = nspi->xfer_udelay;
	rx.speed_hz = nspi->xfer_speed_hz;
	spi_message_add_tail(&rx, &m);

	ret = spi_sync(nspi->spi, &m);
	if (ret)
		goto receive_error;

	if (nspi->acknowledge_mode == NCI_SPI_CRC_ENABLED) {
		*(u8 *)skb_push(skb, 1) = resp_hdr[1];
		*(u8 *)skb_push(skb, 1) = resp_hdr[0];
	}

	return skb;

receive_error:
	kfree_skb(skb);

	return NULL;
}