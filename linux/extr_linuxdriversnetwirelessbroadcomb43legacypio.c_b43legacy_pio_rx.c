#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {int* data; } ;
struct b43legacy_rxhdr_fw3 {int /*<<< orphan*/  mac_status; } ;
struct b43legacy_pioqueue {scalar_t__ mmio_base; TYPE_1__* dev; } ;
struct b43legacy_hwtxstatus {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ B43legacy_MMIO_PIO1_BASE ; 
 scalar_t__ B43legacy_MMIO_PIO4_BASE ; 
 int /*<<< orphan*/  B43legacy_PIO_RXCTL ; 
 int B43legacy_PIO_RXCTL_DATAAVAILABLE ; 
 int B43legacy_PIO_RXCTL_READY ; 
 int /*<<< orphan*/  B43legacy_PIO_RXDATA ; 
 int B43legacy_RX_MAC_FCSERR ; 
 int /*<<< orphan*/  b43legacy_handle_hwtxstatus (TYPE_1__*,struct b43legacy_hwtxstatus*) ; 
 int b43legacy_pio_read (struct b43legacy_pioqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_pio_write (struct b43legacy_pioqueue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_rx (TYPE_1__*,struct sk_buff*,struct b43legacy_rxhdr_fw3*) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pio_rx_error (struct b43legacy_pioqueue*,int,char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

void b43legacy_pio_rx(struct b43legacy_pioqueue *queue)
{
	__le16 preamble[21] = { 0 };
	struct b43legacy_rxhdr_fw3 *rxhdr;
	u16 tmp;
	u16 len;
	u16 macstat;
	int i;
	int preamble_readwords;
	struct sk_buff *skb;

	tmp = b43legacy_pio_read(queue, B43legacy_PIO_RXCTL);
	if (!(tmp & B43legacy_PIO_RXCTL_DATAAVAILABLE))
		return;
	b43legacy_pio_write(queue, B43legacy_PIO_RXCTL,
			    B43legacy_PIO_RXCTL_DATAAVAILABLE);

	for (i = 0; i < 10; i++) {
		tmp = b43legacy_pio_read(queue, B43legacy_PIO_RXCTL);
		if (tmp & B43legacy_PIO_RXCTL_READY)
			goto data_ready;
		udelay(10);
	}
	b43legacydbg(queue->dev->wl, "PIO RX timed out\n");
	return;
data_ready:

	len = b43legacy_pio_read(queue, B43legacy_PIO_RXDATA);
	if (unlikely(len > 0x700)) {
		pio_rx_error(queue, 0, "len > 0x700");
		return;
	}
	if (unlikely(len == 0 && queue->mmio_base !=
		     B43legacy_MMIO_PIO4_BASE)) {
		pio_rx_error(queue, 0, "len == 0");
		return;
	}
	preamble[0] = cpu_to_le16(len);
	if (queue->mmio_base == B43legacy_MMIO_PIO4_BASE)
		preamble_readwords = 14 / sizeof(u16);
	else
		preamble_readwords = 18 / sizeof(u16);
	for (i = 0; i < preamble_readwords; i++) {
		tmp = b43legacy_pio_read(queue, B43legacy_PIO_RXDATA);
		preamble[i + 1] = cpu_to_le16(tmp);
	}
	rxhdr = (struct b43legacy_rxhdr_fw3 *)preamble;
	macstat = le16_to_cpu(rxhdr->mac_status);
	if (macstat & B43legacy_RX_MAC_FCSERR) {
		pio_rx_error(queue,
			     (queue->mmio_base == B43legacy_MMIO_PIO1_BASE),
			     "Frame FCS error");
		return;
	}
	if (queue->mmio_base == B43legacy_MMIO_PIO4_BASE) {
		/* We received an xmit status. */
		struct b43legacy_hwtxstatus *hw;

		hw = (struct b43legacy_hwtxstatus *)(preamble + 1);
		b43legacy_handle_hwtxstatus(queue->dev, hw);

		return;
	}

	skb = dev_alloc_skb(len);
	if (unlikely(!skb)) {
		pio_rx_error(queue, 1, "OOM");
		return;
	}
	skb_put(skb, len);
	for (i = 0; i < len - 1; i += 2) {
		tmp = b43legacy_pio_read(queue, B43legacy_PIO_RXDATA);
		*((__le16 *)(skb->data + i)) = cpu_to_le16(tmp);
	}
	if (len % 2) {
		tmp = b43legacy_pio_read(queue, B43legacy_PIO_RXDATA);
		skb->data[len - 1] = (tmp & 0x00FF);
	}
	b43legacy_rx(queue->dev, skb, rxhdr);
}