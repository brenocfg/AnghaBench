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
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ nla_get_u32 (struct nlattr const*) ; 

__attribute__((used)) static int nl80211_check_u32(const struct nlattr *nla, u32 min, u32 max, u32 *out)
{
	u32 val = nla_get_u32(nla);
	if (val < min || val > max)
		return -EINVAL;
	*out = val;
	return 0;
}