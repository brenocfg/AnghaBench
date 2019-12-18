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
struct xfrmu_sadhinfo {int dummy; } ;

/* Variables and functions */
 unsigned int NLMSG_ALIGN (int) ; 
 unsigned int nla_total_size (int) ; 

__attribute__((used)) static inline unsigned int xfrm_sadinfo_msgsize(void)
{
	return NLMSG_ALIGN(4)
	       + nla_total_size(sizeof(struct xfrmu_sadhinfo))
	       + nla_total_size(4); /* XFRMA_SAD_CNT */
}