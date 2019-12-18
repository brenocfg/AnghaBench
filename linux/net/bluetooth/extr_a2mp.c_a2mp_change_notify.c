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
struct sk_buff {int len; scalar_t__ data; } ;
struct amp_mgr {int dummy; } ;
struct a2mp_cmd {int dummy; } ;
struct a2mp_cl {int /*<<< orphan*/  status; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct a2mp_cl* skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_change_notify(struct amp_mgr *mgr, struct sk_buff *skb,
			      struct a2mp_cmd *hdr)
{
	struct a2mp_cl *cl = (void *) skb->data;

	while (skb->len >= sizeof(*cl)) {
		BT_DBG("Controller id %d type %d status %d", cl->id, cl->type,
		       cl->status);
		cl = skb_pull(skb, sizeof(*cl));
	}

	/* TODO send A2MP_CHANGE_RSP */

	return 0;
}