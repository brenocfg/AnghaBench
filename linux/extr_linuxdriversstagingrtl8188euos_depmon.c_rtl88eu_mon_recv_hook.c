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
struct rx_pkt_attrib {scalar_t__ bdecrypted; int /*<<< orphan*/  encrypt; } ;
struct recv_frame {TYPE_1__* pkt; struct rx_pkt_attrib attrib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ICE_IV_LEN (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_recv_decrypted (struct net_device*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  mon_recv_encrypted (struct net_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

void rtl88eu_mon_recv_hook(struct net_device *dev, struct recv_frame *frame)
{
	struct rx_pkt_attrib *attr;
	int iv_len, icv_len;
	int data_len;
	u8 *data;

	if (!dev || !frame)
		return;
	if (!netif_running(dev))
		return;

	attr = &frame->attrib;
	data = frame->pkt->data;
	data_len = frame->pkt->len;

	/* Broadcast and multicast frames don't have attr->{iv,icv}_len set */
	SET_ICE_IV_LEN(iv_len, icv_len, attr->encrypt);

	if (attr->bdecrypted)
		mon_recv_decrypted(dev, data, data_len, iv_len, icv_len);
	else
		mon_recv_encrypted(dev, data, data_len);
}