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
struct TYPE_2__ {int sort_by_name; int allow_aliases; scalar_t__ vmlinux_name; } ;

/* Variables and functions */
 scalar_t__ host_machine ; 
 scalar_t__ machine__new_host () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  symbol__exit () ; 
 int symbol__init (int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

int init_probe_symbol_maps(bool user_only)
{
	int ret;

	symbol_conf.sort_by_name = true;
	symbol_conf.allow_aliases = true;
	ret = symbol__init(NULL);
	if (ret < 0) {
		pr_debug("Failed to init symbol map.\n");
		goto out;
	}

	if (host_machine || user_only)	/* already initialized */
		return 0;

	if (symbol_conf.vmlinux_name)
		pr_debug("Use vmlinux: %s\n", symbol_conf.vmlinux_name);

	host_machine = machine__new_host();
	if (!host_machine) {
		pr_debug("machine__new_host() failed.\n");
		symbol__exit();
		ret = -1;
	}
out:
	if (ret < 0)
		pr_warning("Failed to init vmlinux path.\n");
	return ret;
}