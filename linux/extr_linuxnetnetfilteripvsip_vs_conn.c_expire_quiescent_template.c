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
struct netns_ipvs {int dummy; } ;
struct ip_vs_dest {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int expire_quiescent_template(struct netns_ipvs *ipvs,
				     struct ip_vs_dest *dest)
{
#ifdef CONFIG_SYSCTL
	return ipvs->sysctl_expire_quiescent_template &&
		(atomic_read(&dest->weight) == 0);
#else
	return 0;
#endif
}