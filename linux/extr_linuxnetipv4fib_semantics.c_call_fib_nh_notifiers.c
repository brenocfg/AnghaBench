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
struct in_device {int dummy; } ;
struct fib_nh_notifier_info {int /*<<< orphan*/  info; struct fib_nh* fib_nh; } ;
struct fib_nh {int nh_flags; int /*<<< orphan*/  nh_dev; } ;
typedef  enum fib_event_type { ____Placeholder_fib_event_type } fib_event_type ;

/* Variables and functions */
#define  FIB_EVENT_NH_ADD 129 
#define  FIB_EVENT_NH_DEL 128 
 int /*<<< orphan*/  IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN (struct in_device*) ; 
 int NOTIFY_DONE ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 struct in_device* __in_dev_get_rtnl (int /*<<< orphan*/ ) ; 
 int call_fib4_notifiers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call_fib_nh_notifiers(struct fib_nh *fib_nh,
				 enum fib_event_type event_type)
{
	struct in_device *in_dev = __in_dev_get_rtnl(fib_nh->nh_dev);
	struct fib_nh_notifier_info info = {
		.fib_nh = fib_nh,
	};

	switch (event_type) {
	case FIB_EVENT_NH_ADD:
		if (fib_nh->nh_flags & RTNH_F_DEAD)
			break;
		if (IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev) &&
		    fib_nh->nh_flags & RTNH_F_LINKDOWN)
			break;
		return call_fib4_notifiers(dev_net(fib_nh->nh_dev), event_type,
					   &info.info);
	case FIB_EVENT_NH_DEL:
		if ((in_dev && IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev) &&
		     fib_nh->nh_flags & RTNH_F_LINKDOWN) ||
		    (fib_nh->nh_flags & RTNH_F_DEAD))
			return call_fib4_notifiers(dev_net(fib_nh->nh_dev),
						   event_type, &info.info);
	default:
		break;
	}

	return NOTIFY_DONE;
}