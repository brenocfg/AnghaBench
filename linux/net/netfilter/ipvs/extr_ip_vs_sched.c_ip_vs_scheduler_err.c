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
struct TYPE_2__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct ip_vs_service {scalar_t__ af; int /*<<< orphan*/  port; TYPE_1__ addr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  scheduler; } ;
struct ip_vs_scheduler {char* name; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IP_VS_ERR_RL (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  ip_vs_proto_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct ip_vs_scheduler* rcu_dereference (int /*<<< orphan*/ ) ; 

void ip_vs_scheduler_err(struct ip_vs_service *svc, const char *msg)
{
	struct ip_vs_scheduler *sched = rcu_dereference(svc->scheduler);
	char *sched_name = sched ? sched->name : "none";

	if (svc->fwmark) {
		IP_VS_ERR_RL("%s: FWM %u 0x%08X - %s\n",
			     sched_name, svc->fwmark, svc->fwmark, msg);
#ifdef CONFIG_IP_VS_IPV6
	} else if (svc->af == AF_INET6) {
		IP_VS_ERR_RL("%s: %s [%pI6c]:%d - %s\n",
			     sched_name, ip_vs_proto_name(svc->protocol),
			     &svc->addr.in6, ntohs(svc->port), msg);
#endif
	} else {
		IP_VS_ERR_RL("%s: %s %pI4:%d - %s\n",
			     sched_name, ip_vs_proto_name(svc->protocol),
			     &svc->addr.ip, ntohs(svc->port), msg);
	}
}