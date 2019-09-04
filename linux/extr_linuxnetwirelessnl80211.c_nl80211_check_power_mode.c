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
typedef  int u32 ;
struct nlattr {int dummy; } ;
typedef  enum nl80211_mesh_power_mode { ____Placeholder_nl80211_mesh_power_mode } nl80211_mesh_power_mode ;

/* Variables and functions */
 int EINVAL ; 
 int nla_get_u32 (struct nlattr const*) ; 

__attribute__((used)) static int nl80211_check_power_mode(const struct nlattr *nla,
				    enum nl80211_mesh_power_mode min,
				    enum nl80211_mesh_power_mode max,
				    enum nl80211_mesh_power_mode *out)
{
	u32 val = nla_get_u32(nla);
	if (val < min || val > max)
		return -EINVAL;
	*out = val;
	return 0;
}