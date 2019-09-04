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
struct notifier_block {int dummy; } ;
struct fib_notifier_info {int dummy; } ;

/* Variables and functions */
#define  FIB_EVENT_ENTRY_ADD 131 
#define  FIB_EVENT_ENTRY_DEL 130 
#define  FIB_EVENT_RULE_ADD 129 
#define  FIB_EVENT_RULE_DEL 128 
 int notifier_from_errno (int) ; 
 int nsim_fib_event (struct fib_notifier_info*,int) ; 
 int nsim_fib_rule_event (struct fib_notifier_info*,int) ; 

__attribute__((used)) static int nsim_fib_event_nb(struct notifier_block *nb, unsigned long event,
			     void *ptr)
{
	struct fib_notifier_info *info = ptr;
	int err = 0;

	switch (event) {
	case FIB_EVENT_RULE_ADD: /* fall through */
	case FIB_EVENT_RULE_DEL:
		err = nsim_fib_rule_event(info, event == FIB_EVENT_RULE_ADD);
		break;

	case FIB_EVENT_ENTRY_ADD:  /* fall through */
	case FIB_EVENT_ENTRY_DEL:
		err = nsim_fib_event(info, event == FIB_EVENT_ENTRY_ADD);
		break;
	}

	return notifier_from_errno(err);
}