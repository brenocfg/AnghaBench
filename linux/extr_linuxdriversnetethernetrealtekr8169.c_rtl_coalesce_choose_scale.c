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
typedef  int u16 ;
struct rtl_coalesce_scale {int /*<<< orphan*/ * nsecs; } ;
struct rtl_coalesce_info {struct rtl_coalesce_scale const* scalev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rtl_coalesce_scale const* ERR_CAST (struct rtl_coalesce_info const*) ; 
 struct rtl_coalesce_scale const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rtl_coalesce_info const*) ; 
 int RTL_COALESCE_T_MAX ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_coalesce_info* rtl_coalesce_info (struct net_device*) ; 

__attribute__((used)) static const struct rtl_coalesce_scale *rtl_coalesce_choose_scale(
			struct net_device *dev, u32 nsec, u16 *cp01)
{
	const struct rtl_coalesce_info *ci;
	u16 i;

	ci = rtl_coalesce_info(dev);
	if (IS_ERR(ci))
		return ERR_CAST(ci);

	for (i = 0; i < 4; i++) {
		u32 rxtx_maxscale = max(ci->scalev[i].nsecs[0],
					ci->scalev[i].nsecs[1]);
		if (nsec <= rxtx_maxscale * RTL_COALESCE_T_MAX) {
			*cp01 = i;
			return &ci->scalev[i];
		}
	}

	return ERR_PTR(-EINVAL);
}