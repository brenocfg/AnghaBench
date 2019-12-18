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
struct devlink_health_reporter {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devlink_health_reporter_put(struct devlink_health_reporter *reporter)
{
	refcount_dec(&reporter->refcount);
}