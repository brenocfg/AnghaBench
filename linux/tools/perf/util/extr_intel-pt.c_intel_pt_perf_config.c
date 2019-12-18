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
struct intel_pt {int /*<<< orphan*/  mispred_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int intel_pt_perf_config(const char *var, const char *value, void *data)
{
	struct intel_pt *pt = data;

	if (!strcmp(var, "intel-pt.mispred-all"))
		pt->mispred_all = perf_config_bool(var, value);

	return 0;
}