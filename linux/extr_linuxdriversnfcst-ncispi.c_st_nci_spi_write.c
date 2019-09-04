#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct st_nci_spi_phy {TYPE_1__* ndlc; struct spi_device* spi_dev; } ;
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ hard_fault; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NCI_DATA_HDR_SIZE ; 
 int ST_NCI_FRAME_HEADROOM ; 
 int ST_NCI_FRAME_TAILROOM ; 
 int ST_NCI_SPI_MAX_SIZE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndlc_recv (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int spi_sync_transfer (struct spi_device*,struct spi_transfer*,int) ; 

__attribute__((used)) static int st_nci_spi_write(void *phy_id, struct sk_buff *skb)
{
	int r;
	struct st_nci_spi_phy *phy = phy_id;
	struct spi_device *dev = phy->spi_dev;
	struct sk_buff *skb_rx;
	u8 buf[ST_NCI_SPI_MAX_SIZE + NCI_DATA_HDR_SIZE +
	       ST_NCI_FRAME_HEADROOM + ST_NCI_FRAME_TAILROOM];
	struct spi_transfer spi_xfer = {
		.tx_buf = skb->data,
		.rx_buf = buf,
		.len = skb->len,
	};

	if (phy->ndlc->hard_fault != 0)
		return phy->ndlc->hard_fault;

	r = spi_sync_transfer(dev, &spi_xfer, 1);
	/*
	 * We may have received some valuable data on miso line.
	 * Send them back in the ndlc state machine.
	 */
	if (!r) {
		skb_rx = alloc_skb(skb->len, GFP_KERNEL);
		if (!skb_rx) {
			r = -ENOMEM;
			goto exit;
		}

		skb_put(skb_rx, skb->len);
		memcpy(skb_rx->data, buf, skb->len);
		ndlc_recv(phy->ndlc, skb_rx);
	}

exit:
	return r;
}