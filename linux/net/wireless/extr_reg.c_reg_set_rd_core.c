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
struct ieee80211_regdomain {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_world_regdom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_world_regdomain (struct ieee80211_regdomain const*) ; 

__attribute__((used)) static int reg_set_rd_core(const struct ieee80211_regdomain *rd)
{
	if (!is_world_regdom(rd->alpha2))
		return -EINVAL;
	update_world_regdomain(rd);
	return 0;
}