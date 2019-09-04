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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct pkt_attrib {int nr_frags; int /*<<< orphan*/  iv_len; int /*<<< orphan*/  last_txcmdsz; } ;
struct xmit_frame {int pkt_offset; int /*<<< orphan*/ * buf_addr; struct pkt_attrib attrib; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int PACKET_OFFSET_SZ ; 
 int TXDESC_SIZE ; 
 int /*<<< orphan*/  mon_recv_decrypted (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ round_up (size_t,int) ; 

void rtl88eu_mon_xmit_hook(struct net_device *dev, struct xmit_frame *frame,
			   uint frag_len)
{
	struct pkt_attrib *attr;
	u8 *data;
	int i, offset;

	if (!dev || !frame)
		return;
	if (!netif_running(dev))
		return;

	attr = &frame->attrib;

	offset = TXDESC_SIZE + frame->pkt_offset * PACKET_OFFSET_SZ;
	data = frame->buf_addr + offset;

	for (i = 0; i < attr->nr_frags - 1; i++) {
		mon_recv_decrypted(dev, data, frag_len, attr->iv_len, 0);
		data += frag_len;
		data = (u8 *)round_up((size_t)data, 4);
	}
	/* Last fragment has different length */
	mon_recv_decrypted(dev, data, attr->last_txcmdsz, attr->iv_len, 0);
}