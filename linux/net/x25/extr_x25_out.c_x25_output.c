#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pacsize_out; } ;
struct x25_sock {TYPE_2__* neighbour; TYPE_1__ facilities; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ extended; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*,int,int) ; 
 int X25_EXT_MIN_LEN ; 
 int /*<<< orphan*/  X25_EXT_M_BIT ; 
 TYPE_3__* X25_SKB_CB (struct sk_buff*) ; 
 int X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  X25_STD_M_BIT ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int,int,int*) ; 
 int x25_pacsize_to_bytes (int /*<<< orphan*/ ) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

int x25_output(struct sock *sk, struct sk_buff *skb)
{
	struct sk_buff *skbn;
	unsigned char header[X25_EXT_MIN_LEN];
	int err, frontlen, len;
	int sent=0, noblock = X25_SKB_CB(skb)->flags & MSG_DONTWAIT;
	struct x25_sock *x25 = x25_sk(sk);
	int header_len = x25->neighbour->extended ? X25_EXT_MIN_LEN :
						    X25_STD_MIN_LEN;
	int max_len = x25_pacsize_to_bytes(x25->facilities.pacsize_out);

	if (skb->len - header_len > max_len) {
		/* Save a copy of the Header */
		skb_copy_from_linear_data(skb, header, header_len);
		skb_pull(skb, header_len);

		frontlen = skb_headroom(skb);

		while (skb->len > 0) {
			release_sock(sk);
			skbn = sock_alloc_send_skb(sk, frontlen + max_len,
						   noblock, &err);
			lock_sock(sk);
			if (!skbn) {
				if (err == -EWOULDBLOCK && noblock){
					kfree_skb(skb);
					return sent;
				}
				SOCK_DEBUG(sk, "x25_output: fragment alloc"
					       " failed, err=%d, %d bytes "
					       "sent\n", err, sent);
				return err;
			}

			skb_reserve(skbn, frontlen);

			len = max_len > skb->len ? skb->len : max_len;

			/* Copy the user data */
			skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
			skb_pull(skb, len);

			/* Duplicate the Header */
			skb_push(skbn, header_len);
			skb_copy_to_linear_data(skbn, header, header_len);

			if (skb->len > 0) {
				if (x25->neighbour->extended)
					skbn->data[3] |= X25_EXT_M_BIT;
				else
					skbn->data[2] |= X25_STD_M_BIT;
			}

			skb_queue_tail(&sk->sk_write_queue, skbn);
			sent += len;
		}

		kfree_skb(skb);
	} else {
		skb_queue_tail(&sk->sk_write_queue, skb);
		sent = skb->len - header_len;
	}
	return sent;
}