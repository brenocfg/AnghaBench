#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int ee_data; int ee_info; scalar_t__ ee_pad; int /*<<< orphan*/  ee_code; scalar_t__ ee_type; int /*<<< orphan*/  ee_origin; int /*<<< orphan*/  ee_errno; } ;
struct sock_exterr_skb {TYPE_1__ ee; } ;
struct sk_buff {int tstamp; TYPE_2__* sk; } ;
typedef  int ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  sk_txtime_report_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_TXTIME ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_queue_err_skb (TYPE_2__*,struct sk_buff*) ; 

__attribute__((used)) static void report_sock_error(struct sk_buff *skb, u32 err, u8 code)
{
	struct sock_exterr_skb *serr;
	struct sk_buff *clone;
	ktime_t txtime = skb->tstamp;

	if (!skb->sk || !(skb->sk->sk_txtime_report_errors))
		return;

	clone = skb_clone(skb, GFP_ATOMIC);
	if (!clone)
		return;

	serr = SKB_EXT_ERR(clone);
	serr->ee.ee_errno = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXTIME;
	serr->ee.ee_type = 0;
	serr->ee.ee_code = code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_data = (txtime >> 32); /* high part of tstamp */
	serr->ee.ee_info = txtime; /* low part of tstamp */

	if (sock_queue_err_skb(skb->sk, clone))
		kfree_skb(clone);
}