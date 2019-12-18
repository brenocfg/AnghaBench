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
struct x25_sock {int condition; int /*<<< orphan*/  state; int /*<<< orphan*/  vl; int /*<<< orphan*/  vs; int /*<<< orphan*/  vr; int /*<<< orphan*/  va; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int const X25_CLEAR_CONFIRMATION ; 
#define  X25_CLEAR_REQUEST 130 
#define  X25_RESET_CONFIRMATION 129 
#define  X25_RESET_REQUEST 128 
 int /*<<< orphan*/  X25_STATE_2 ; 
 int /*<<< orphan*/  X25_STATE_3 ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_requeue_frames (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_t23timer (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int const) ; 

__attribute__((used)) static int x25_state4_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	struct x25_sock *x25 = x25_sk(sk);

	switch (frametype) {

		case X25_RESET_REQUEST:
			x25_write_internal(sk, X25_RESET_CONFIRMATION);
			/* fall through */
		case X25_RESET_CONFIRMATION: {
			x25_stop_timer(sk);
			x25->condition = 0x00;
			x25->va        = 0;
			x25->vr        = 0;
			x25->vs        = 0;
			x25->vl        = 0;
			x25->state     = X25_STATE_3;
			x25_requeue_frames(sk);
			break;
		}
		case X25_CLEAR_REQUEST:
			if (!pskb_may_pull(skb, X25_STD_MIN_LEN + 2))
				goto out_clear;

			x25_write_internal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			break;

		default:
			break;
	}

	return 0;

out_clear:
	x25_write_internal(sk, X25_CLEAR_REQUEST);
	x25->state = X25_STATE_2;
	x25_start_t23timer(sk);
	return 0;
}