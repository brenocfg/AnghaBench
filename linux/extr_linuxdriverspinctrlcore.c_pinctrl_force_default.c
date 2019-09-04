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
struct pinctrl_dev {int /*<<< orphan*/  hog_default; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int pinctrl_commit_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pinctrl_force_default(struct pinctrl_dev *pctldev)
{
	if (!IS_ERR(pctldev->p) && !IS_ERR(pctldev->hog_default))
		return pinctrl_commit_state(pctldev->p, pctldev->hog_default);
	return 0;
}