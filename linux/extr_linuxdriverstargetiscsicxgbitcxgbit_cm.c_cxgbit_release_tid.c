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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct cxgbit_device {int dummy; } ;
struct cpl_tid_release {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_mk_tid_release (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbit_ofld_send (struct cxgbit_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  roundup (int,int) ; 

__attribute__((used)) static void cxgbit_release_tid(struct cxgbit_device *cdev, u32 tid)
{
	u32 len = roundup(sizeof(struct cpl_tid_release), 16);
	struct sk_buff *skb;

	skb = alloc_skb(len, GFP_ATOMIC);
	if (!skb)
		return;

	cxgb_mk_tid_release(skb, len, tid, 0);
	cxgbit_ofld_send(cdev, skb);
}