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
struct platform_device {int dummy; } ;
struct da9150_fg {int /*<<< orphan*/  work; scalar_t__ interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct da9150_fg* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int da9150_fg_remove(struct platform_device *pdev)
{
	struct da9150_fg *fg = platform_get_drvdata(pdev);

	if (fg->interval)
		cancel_delayed_work(&fg->work);

	return 0;
}