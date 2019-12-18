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
struct xfrm_policy {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct km_event {int event; TYPE_1__ data; } ;

/* Variables and functions */
#define  XFRM_MSG_DELPOLICY 132 
#define  XFRM_MSG_FLUSHPOLICY 131 
#define  XFRM_MSG_NEWPOLICY 130 
#define  XFRM_MSG_POLEXPIRE 129 
#define  XFRM_MSG_UPDPOLICY 128 
 scalar_t__ XFRM_POLICY_TYPE_MAIN ; 
 int key_notify_policy (struct xfrm_policy*,int,struct km_event const*) ; 
 int key_notify_policy_expire (struct xfrm_policy*,struct km_event const*) ; 
 int key_notify_policy_flush (struct km_event const*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int pfkey_send_policy_notify(struct xfrm_policy *xp, int dir, const struct km_event *c)
{
	if (xp && xp->type != XFRM_POLICY_TYPE_MAIN)
		return 0;

	switch (c->event) {
	case XFRM_MSG_POLEXPIRE:
		return key_notify_policy_expire(xp, c);
	case XFRM_MSG_DELPOLICY:
	case XFRM_MSG_NEWPOLICY:
	case XFRM_MSG_UPDPOLICY:
		return key_notify_policy(xp, dir, c);
	case XFRM_MSG_FLUSHPOLICY:
		if (c->data.type != XFRM_POLICY_TYPE_MAIN)
			break;
		return key_notify_policy_flush(c);
	default:
		pr_err("pfkey: Unknown policy event %d\n", c->event);
		break;
	}

	return 0;
}