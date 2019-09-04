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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACERHDF_FAN_AUTO ; 
 int /*<<< orphan*/  acerhdf_change_fanstate (int /*<<< orphan*/ ) ; 
 scalar_t__ kernelmode ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int acerhdf_suspend(struct device *dev)
{
	if (kernelmode)
		acerhdf_change_fanstate(ACERHDF_FAN_AUTO);

	if (verbose)
		pr_notice("going suspend\n");

	return 0;
}