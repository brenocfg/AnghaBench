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
struct ip_vs_service {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_service_free (struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_service_rcu_free ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ip_vs_svc_put(struct ip_vs_service *svc, bool do_delay)
{
	if (atomic_dec_and_test(&svc->refcnt)) {
		IP_VS_DBG_BUF(3, "Removing service %u/%s:%u\n",
			      svc->fwmark,
			      IP_VS_DBG_ADDR(svc->af, &svc->addr),
			      ntohs(svc->port));
		if (do_delay)
			call_rcu(&svc->rcu_head, ip_vs_service_rcu_free);
		else
			ip_vs_service_free(svc);
	}
}