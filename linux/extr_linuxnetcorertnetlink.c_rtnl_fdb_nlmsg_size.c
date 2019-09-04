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
typedef  int /*<<< orphan*/  u16 ;
struct ndmsg {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t rtnl_fdb_nlmsg_size(void)
{
	return NLMSG_ALIGN(sizeof(struct ndmsg)) +
	       nla_total_size(ETH_ALEN) +	/* NDA_LLADDR */
	       nla_total_size(sizeof(u16)) +	/* NDA_VLAN */
	       0;
}