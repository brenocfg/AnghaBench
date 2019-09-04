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
struct rproc {int /*<<< orphan*/  crash_handler; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
typedef  enum rproc_crash_type { ____Placeholder_rproc_crash_type } rproc_crash_type ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rproc_crash_to_string (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void rproc_report_crash(struct rproc *rproc, enum rproc_crash_type type)
{
	if (!rproc) {
		pr_err("NULL rproc pointer\n");
		return;
	}

	dev_err(&rproc->dev, "crash detected in %s: type %s\n",
		rproc->name, rproc_crash_to_string(type));

	/* create a new task to handle the error */
	schedule_work(&rproc->crash_handler);
}