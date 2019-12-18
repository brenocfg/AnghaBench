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
struct itrace_synth_opts {scalar_t__ last_branch; scalar_t__ thread_stack; scalar_t__ callchain; scalar_t__ returns; scalar_t__ calls; scalar_t__ dont_decode; scalar_t__ errors; scalar_t__ pwr_events; scalar_t__ ptwrites; scalar_t__ transactions; scalar_t__ branches; scalar_t__ instructions; scalar_t__ inject; int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static bool check_auxtrace_itrace(struct itrace_synth_opts *itops)
{
	bool ison = false;

	if (!itops || !itops->set)
		return true;
	ison = itops->inject || itops->instructions || itops->branches ||
		itops->transactions || itops->ptwrites ||
		itops->pwr_events || itops->errors ||
		itops->dont_decode || itops->calls || itops->returns ||
		itops->callchain || itops->thread_stack ||
		itops->last_branch;
	if (!ison)
		return true;
	pr_err("Unsupported --itrace options specified\n");
	return false;
}