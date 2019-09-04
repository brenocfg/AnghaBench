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
struct callchain_param {scalar_t__ mode; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  sym; } ;

/* Variables and functions */
 scalar_t__ CHAIN_NONE ; 
 int EINVAL ; 
 scalar_t__ callchain_register_param (struct callchain_param*) ; 
 TYPE_1__ perf_hpp_list ; 
 int /*<<< orphan*/  ui__error (char*) ; 

__attribute__((used)) static int callchain_param__setup_sample_type(struct callchain_param *callchain)
{
	if (!perf_hpp_list.sym) {
		if (callchain->enabled) {
			ui__error("Selected -g but \"sym\" not present in --sort/-s.");
			return -EINVAL;
		}
	} else if (callchain->mode != CHAIN_NONE) {
		if (callchain_register_param(callchain) < 0) {
			ui__error("Can't register callchain params.\n");
			return -EINVAL;
		}
	}

	return 0;
}