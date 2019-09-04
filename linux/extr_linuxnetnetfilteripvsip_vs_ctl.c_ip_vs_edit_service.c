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
struct ip_vs_service_user_kern {int flags; int timeout; int /*<<< orphan*/  netmask; scalar_t__* pe_name; scalar_t__* sched_name; } ;
struct ip_vs_service {int flags; int timeout; TYPE_1__* ipvs; int /*<<< orphan*/  pe; int /*<<< orphan*/  netmask; int /*<<< orphan*/  scheduler; } ;
struct ip_vs_scheduler {int dummy; } ;
struct ip_vs_pe {scalar_t__ conn_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn_out_counter; } ;

/* Variables and functions */
 int ENOENT ; 
 int HZ ; 
 int IP_VS_SVC_F_HASHED ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ip_vs_bind_scheduler (struct ip_vs_service*,struct ip_vs_scheduler*) ; 
 struct ip_vs_pe* ip_vs_pe_getbyname (scalar_t__*) ; 
 int /*<<< orphan*/  ip_vs_pe_put (struct ip_vs_pe*) ; 
 struct ip_vs_scheduler* ip_vs_scheduler_get (scalar_t__*) ; 
 int /*<<< orphan*/  ip_vs_scheduler_put (struct ip_vs_scheduler*) ; 
 int /*<<< orphan*/  ip_vs_unbind_scheduler (struct ip_vs_service*,struct ip_vs_scheduler*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ip_vs_pe*) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int
ip_vs_edit_service(struct ip_vs_service *svc, struct ip_vs_service_user_kern *u)
{
	struct ip_vs_scheduler *sched = NULL, *old_sched;
	struct ip_vs_pe *pe = NULL, *old_pe = NULL;
	int ret = 0;
	bool new_pe_conn_out, old_pe_conn_out;

	/*
	 * Lookup the scheduler, by 'u->sched_name'
	 */
	if (strcmp(u->sched_name, "none")) {
		sched = ip_vs_scheduler_get(u->sched_name);
		if (!sched) {
			pr_info("Scheduler module ip_vs_%s not found\n",
				u->sched_name);
			return -ENOENT;
		}
	}
	old_sched = sched;

	if (u->pe_name && *u->pe_name) {
		pe = ip_vs_pe_getbyname(u->pe_name);
		if (pe == NULL) {
			pr_info("persistence engine module ip_vs_pe_%s "
				"not found\n", u->pe_name);
			ret = -ENOENT;
			goto out;
		}
		old_pe = pe;
	}

#ifdef CONFIG_IP_VS_IPV6
	if (u->af == AF_INET6) {
		__u32 plen = (__force __u32) u->netmask;

		if (plen < 1 || plen > 128) {
			ret = -EINVAL;
			goto out;
		}
	}
#endif

	old_sched = rcu_dereference_protected(svc->scheduler, 1);
	if (sched != old_sched) {
		if (old_sched) {
			ip_vs_unbind_scheduler(svc, old_sched);
			RCU_INIT_POINTER(svc->scheduler, NULL);
			/* Wait all svc->sched_data users */
			synchronize_rcu();
		}
		/* Bind the new scheduler */
		if (sched) {
			ret = ip_vs_bind_scheduler(svc, sched);
			if (ret) {
				ip_vs_scheduler_put(sched);
				goto out;
			}
		}
	}

	/*
	 * Set the flags and timeout value
	 */
	svc->flags = u->flags | IP_VS_SVC_F_HASHED;
	svc->timeout = u->timeout * HZ;
	svc->netmask = u->netmask;

	old_pe = rcu_dereference_protected(svc->pe, 1);
	if (pe != old_pe) {
		rcu_assign_pointer(svc->pe, pe);
		/* check for optional methods in new pe */
		new_pe_conn_out = (pe && pe->conn_out) ? true : false;
		old_pe_conn_out = (old_pe && old_pe->conn_out) ? true : false;
		if (new_pe_conn_out && !old_pe_conn_out)
			atomic_inc(&svc->ipvs->conn_out_counter);
		if (old_pe_conn_out && !new_pe_conn_out)
			atomic_dec(&svc->ipvs->conn_out_counter);
	}

out:
	ip_vs_scheduler_put(old_sched);
	ip_vs_pe_put(old_pe);
	return ret;
}