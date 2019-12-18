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
struct xt_mtchk_param {struct ip6t_icmp* matchinfo; } ;
struct ip6t_icmp {int invflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_ICMP_INV ; 

__attribute__((used)) static int icmp6_checkentry(const struct xt_mtchk_param *par)
{
	const struct ip6t_icmp *icmpinfo = par->matchinfo;

	/* Must specify no unknown invflags */
	return (icmpinfo->invflags & ~IP6T_ICMP_INV) ? -EINVAL : 0;
}