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
typedef  int u8 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nla_get_u8 (struct nlattr const*) ; 

__attribute__((used)) static int nl80211_check_bool(const struct nlattr *nla, u8 min, u8 max, bool *out)
{
	u8 val = nla_get_u8(nla);
	if (val < min || val > max)
		return -EINVAL;
	*out = val;
	return 0;
}