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
 unsigned int IFLA_STATS_FILTER_BIT (int) ; 

__attribute__((used)) static bool stats_attr_valid(unsigned int mask, int attrid, int idxattr)
{
	return (mask & IFLA_STATS_FILTER_BIT(attrid)) &&
	       (!idxattr || idxattr == attrid);
}