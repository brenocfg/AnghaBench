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
struct devlink_health_reporter {int /*<<< orphan*/ * dump_fmsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_fmsg_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devlink_health_dump_clear(struct devlink_health_reporter *reporter)
{
	if (!reporter->dump_fmsg)
		return;
	devlink_fmsg_free(reporter->dump_fmsg);
	reporter->dump_fmsg = NULL;
}