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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct hidp_session {int /*<<< orphan*/  terminate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,unsigned char const*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char const*,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,unsigned char) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidp_send_message(struct hidp_session *session, struct socket *sock,
			     struct sk_buff_head *transmit, unsigned char hdr,
			     const unsigned char *data, int size)
{
	struct sk_buff *skb;
	struct sock *sk = sock->sk;
	int ret;

	BT_DBG("session %p data %p size %d", session, data, size);

	if (atomic_read(&session->terminate))
		return -EIO;

	skb = alloc_skb(size + 1, GFP_ATOMIC);
	if (!skb) {
		BT_ERR("Can't allocate memory for new frame");
		return -ENOMEM;
	}

	skb_put_u8(skb, hdr);
	if (data && size > 0) {
		skb_put_data(skb, data, size);
		ret = size;
	} else {
		ret = 0;
	}

	skb_queue_tail(transmit, skb);
	wake_up_interruptible(sk_sleep(sk));

	return ret;
}