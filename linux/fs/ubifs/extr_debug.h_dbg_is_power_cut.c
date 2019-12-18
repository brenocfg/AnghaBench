#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {TYPE_1__* dbg; } ;
struct TYPE_2__ {int /*<<< orphan*/  pc_happened; } ;

/* Variables and functions */

__attribute__((used)) static inline int dbg_is_power_cut(const struct ubifs_info *c)
{
	return !!c->dbg->pc_happened;
}