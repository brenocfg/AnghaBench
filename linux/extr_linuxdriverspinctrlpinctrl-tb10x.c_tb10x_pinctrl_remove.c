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
struct tb10x_pinctrl {int /*<<< orphan*/  mutex; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct tb10x_pinctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tb10x_pinctrl_remove(struct platform_device *pdev)
{
	struct tb10x_pinctrl *state = platform_get_drvdata(pdev);

	mutex_destroy(&state->mutex);

	return 0;
}