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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct notifier_block {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_ntf_refcnt ; 
 int /*<<< orphan*/  nlm_ntf_wq ; 
 TYPE_2__* nlmsvc_rqst ; 
 int /*<<< orphan*/  svc_age_temp_xprts_now (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lockd_inetaddr_event(struct notifier_block *this,
	unsigned long event, void *ptr)
{
	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct sockaddr_in sin;

	if ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nlm_ntf_refcnt))
		goto out;

	if (nlmsvc_rqst) {
		dprintk("lockd_inetaddr_event: removed %pI4\n",
			&ifa->ifa_local);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = ifa->ifa_local;
		svc_age_temp_xprts_now(nlmsvc_rqst->rq_server,
			(struct sockaddr *)&sin);
	}
	atomic_dec(&nlm_ntf_refcnt);
	wake_up(&nlm_ntf_wq);

out:
	return NOTIFY_DONE;
}