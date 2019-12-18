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

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t rtnl_xdp_size(void)
{
	size_t xdp_size = nla_total_size(0) +	/* nest IFLA_XDP */
			  nla_total_size(1) +	/* XDP_ATTACHED */
			  nla_total_size(4) +	/* XDP_PROG_ID (or 1st mode) */
			  nla_total_size(4);	/* XDP_<mode>_PROG_ID */

	return xdp_size;
}