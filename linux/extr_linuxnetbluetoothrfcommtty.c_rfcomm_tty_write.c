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
struct tty_struct {scalar_t__ driver_data; } ;
struct sk_buff {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  mtu; } ;
struct rfcomm_dev {struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RFCOMM_SKB_HEAD_RESERVE ; 
 scalar_t__ RFCOMM_SKB_RESERVE ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_send_noerror (struct rfcomm_dlc*,struct sk_buff*) ; 
 struct sk_buff* rfcomm_wmalloc (struct rfcomm_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char const*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static int rfcomm_tty_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;
	struct rfcomm_dlc *dlc = dev->dlc;
	struct sk_buff *skb;
	int sent = 0, size;

	BT_DBG("tty %p count %d", tty, count);

	while (count) {
		size = min_t(uint, count, dlc->mtu);

		skb = rfcomm_wmalloc(dev, size + RFCOMM_SKB_RESERVE, GFP_ATOMIC);
		if (!skb)
			break;

		skb_reserve(skb, RFCOMM_SKB_HEAD_RESERVE);

		skb_put_data(skb, buf + sent, size);

		rfcomm_dlc_send_noerror(dlc, skb);

		sent  += size;
		count -= size;
	}

	return sent;
}