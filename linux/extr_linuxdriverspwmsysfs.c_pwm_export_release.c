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
struct pwm_export {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pwm_export* child_to_pwm_export (struct device*) ; 
 int /*<<< orphan*/  kfree (struct pwm_export*) ; 

__attribute__((used)) static void pwm_export_release(struct device *child)
{
	struct pwm_export *export = child_to_pwm_export(child);

	kfree(export);
}