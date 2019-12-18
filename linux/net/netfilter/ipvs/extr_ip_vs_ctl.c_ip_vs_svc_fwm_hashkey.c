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
typedef  size_t __u32 ;

/* Variables and functions */
 size_t IP_VS_SVC_TAB_MASK ; 

__attribute__((used)) static inline unsigned int ip_vs_svc_fwm_hashkey(struct netns_ipvs *ipvs, __u32 fwmark)
{
	return (((size_t)ipvs>>8) ^ fwmark) & IP_VS_SVC_TAB_MASK;
}