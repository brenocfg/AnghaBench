#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {scalar_t__ (* recv ) (struct nci_uart*,TYPE_3__*) ;} ;
struct nci_uart {int rx_packet_len; TYPE_3__* rx_skb; TYPE_2__* tty; TYPE_1__ ops; int /*<<< orphan*/  ndev; } ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NCI_CTRL_HDR_SIZE ; 
 int /*<<< orphan*/  NCI_MAX_PACKET_SIZE ; 
 scalar_t__ nci_plen (int /*<<< orphan*/ ) ; 
 TYPE_3__* nci_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_put_data (TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct nci_uart*,TYPE_3__*) ; 

__attribute__((used)) static int nci_uart_default_recv_buf(struct nci_uart *nu, const u8 *data,
				     char *flags, int count)
{
	int chunk_len;

	if (!nu->ndev) {
		nfc_err(nu->tty->dev,
			"receive data from tty but no NCI dev is attached yet, drop buffer\n");
		return 0;
	}

	/* Decode all incoming data in packets
	 * and enqueue then for processing.
	 */
	while (count > 0) {
		/* If this is the first data of a packet, allocate a buffer */
		if (!nu->rx_skb) {
			nu->rx_packet_len = -1;
			nu->rx_skb = nci_skb_alloc(nu->ndev,
						   NCI_MAX_PACKET_SIZE,
						   GFP_KERNEL);
			if (!nu->rx_skb)
				return -ENOMEM;
		}

		/* Eat byte after byte till full packet header is received */
		if (nu->rx_skb->len < NCI_CTRL_HDR_SIZE) {
			skb_put_u8(nu->rx_skb, *data++);
			--count;
			continue;
		}

		/* Header was received but packet len was not read */
		if (nu->rx_packet_len < 0)
			nu->rx_packet_len = NCI_CTRL_HDR_SIZE +
				nci_plen(nu->rx_skb->data);

		/* Compute how many bytes are missing and how many bytes can
		 * be consumed.
		 */
		chunk_len = nu->rx_packet_len - nu->rx_skb->len;
		if (count < chunk_len)
			chunk_len = count;
		skb_put_data(nu->rx_skb, data, chunk_len);
		data += chunk_len;
		count -= chunk_len;

		/* Chcek if packet is fully received */
		if (nu->rx_packet_len == nu->rx_skb->len) {
			/* Pass RX packet to driver */
			if (nu->ops.recv(nu, nu->rx_skb) != 0)
				nfc_err(nu->tty->dev, "corrupted RX packet\n");
			/* Next packet will be a new one */
			nu->rx_skb = NULL;
		}
	}

	return 0;
}