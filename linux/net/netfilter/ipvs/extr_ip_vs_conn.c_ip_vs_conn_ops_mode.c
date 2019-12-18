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
struct ip_vs_service {int flags; } ;
struct ip_vs_conn {TYPE_1__* dest; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int IP_VS_SVC_F_ONEPACKET ; 
 struct ip_vs_service* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ip_vs_conn_ops_mode(struct ip_vs_conn *cp)
{
	struct ip_vs_service *svc;

	if (!cp->dest)
		return false;
	svc = rcu_dereference(cp->dest->svc);
	return svc && (svc->flags & IP_VS_SVC_F_ONEPACKET);
}