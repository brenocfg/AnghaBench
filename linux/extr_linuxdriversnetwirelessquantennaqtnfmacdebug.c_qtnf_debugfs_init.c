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
struct qtnf_bus {int /*<<< orphan*/ * dbg_dir; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void qtnf_debugfs_init(struct qtnf_bus *bus, const char *name)
{
	bus->dbg_dir = debugfs_create_dir(name, NULL);

	if (IS_ERR_OR_NULL(bus->dbg_dir)) {
		pr_warn("failed to create debugfs root dir\n");
		bus->dbg_dir = NULL;
	}
}