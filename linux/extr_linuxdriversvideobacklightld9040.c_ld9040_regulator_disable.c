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
struct ld9040 {int enabled; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supplies ; 

__attribute__((used)) static void ld9040_regulator_disable(struct ld9040 *lcd)
{
	int ret = 0;

	mutex_lock(&lcd->lock);
	if (lcd->enabled) {
		ret = regulator_bulk_disable(ARRAY_SIZE(supplies), supplies);
		if (ret)
			goto out;

		lcd->enabled = false;
	}
out:
	mutex_unlock(&lcd->lock);
}