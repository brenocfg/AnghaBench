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
struct ip_vs_service {TYPE_1__* ipvs; } ;
struct TYPE_2__ {int sysctl_lblc_expiration; } ;

/* Variables and functions */
 int DEFAULT_EXPIRATION ; 

__attribute__((used)) static int sysctl_lblc_expiration(struct ip_vs_service *svc)
{
#ifdef CONFIG_SYSCTL
	return svc->ipvs->sysctl_lblc_expiration;
#else
	return DEFAULT_EXPIRATION;
#endif
}