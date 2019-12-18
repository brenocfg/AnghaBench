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
struct fib_nh_notifier_info {int /*<<< orphan*/  info; struct fib_nh* fib_nh; } ;
struct fib_nh {int fib_nh_flags; int /*<<< orphan*/  fib_nh_dev; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
#define  FIB_EVENT_NH_ADD 129 
#define  FIB_EVENT_NH_DEL 128 
 int NOTIFY_DONE ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 int call_fib4_notifiers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int ip_ignore_linkdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call_fib_nh_notifiers(struct fib_nh *nh,
				 enum fib_event_type event_type)
{
	bool ignore_link_down = ip_ignore_linkdown(nh->fib_nh_dev);
	struct fib_nh_notifier_info info = {
		.fib_nh = nh,
	};

	switch (event_type) {
	case FIB_EVENT_NH_ADD:
		if (nh->fib_nh_flags & RTNH_F_DEAD)
			break;
		if (ignore_link_down && nh->fib_nh_flags & RTNH_F_LINKDOWN)
			break;
		return call_fib4_notifiers(dev_net(nh->fib_nh_dev), event_type,
					   &info.info);
	case FIB_EVENT_NH_DEL:
		if ((ignore_link_down && nh->fib_nh_flags & RTNH_F_LINKDOWN) ||
		    (nh->fib_nh_flags & RTNH_F_DEAD))
			return call_fib4_notifiers(dev_net(nh->fib_nh_dev),
						   event_type, &info.info);
	default:
		break;
	}

	return NOTIFY_DONE;
}