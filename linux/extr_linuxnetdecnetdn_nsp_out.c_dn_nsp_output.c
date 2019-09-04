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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dn_scp {scalar_t__ flowrem_sw; int snd_window; int /*<<< orphan*/  data_xmit_queue; int /*<<< orphan*/  other_xmit_queue; } ;

/* Variables and functions */
 scalar_t__ DN_SEND ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NSP_MIN_WINDOW ; 
 unsigned int dn_nsp_clone_and_send (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

void dn_nsp_output(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
	struct sk_buff *skb;
	unsigned int reduce_win = 0;

	/*
	 * First we check for otherdata/linkservice messages
	 */
	if ((skb = skb_peek(&scp->other_xmit_queue)) != NULL)
		reduce_win = dn_nsp_clone_and_send(skb, GFP_ATOMIC);

	/*
	 * If we may not send any data, we don't.
	 * If we are still trying to get some other data down the
	 * channel, we don't try and send any data.
	 */
	if (reduce_win || (scp->flowrem_sw != DN_SEND))
		goto recalc_window;

	if ((skb = skb_peek(&scp->data_xmit_queue)) != NULL)
		reduce_win = dn_nsp_clone_and_send(skb, GFP_ATOMIC);

	/*
	 * If we've sent any frame more than once, we cut the
	 * send window size in half. There is always a minimum
	 * window size of one available.
	 */
recalc_window:
	if (reduce_win) {
		scp->snd_window >>= 1;
		if (scp->snd_window < NSP_MIN_WINDOW)
			scp->snd_window = NSP_MIN_WINDOW;
	}
}