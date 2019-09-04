#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* hog_sleep; TYPE_1__* p; TYPE_1__* hog_default; } ;
struct TYPE_7__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int /*<<< orphan*/  PINCTRL_STATE_SLEEP ; 
 int PTR_ERR (TYPE_1__*) ; 
 TYPE_1__* create_pinctrl (int /*<<< orphan*/ ,struct pinctrl_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 void* pinctrl_lookup_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pinctrl_select_state (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int pinctrl_claim_hogs(struct pinctrl_dev *pctldev)
{
	pctldev->p = create_pinctrl(pctldev->dev, pctldev);
	if (PTR_ERR(pctldev->p) == -ENODEV) {
		dev_dbg(pctldev->dev, "no hogs found\n");

		return 0;
	}

	if (IS_ERR(pctldev->p)) {
		dev_err(pctldev->dev, "error claiming hogs: %li\n",
			PTR_ERR(pctldev->p));

		return PTR_ERR(pctldev->p);
	}

	kref_get(&pctldev->p->users);
	pctldev->hog_default =
		pinctrl_lookup_state(pctldev->p, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pctldev->hog_default)) {
		dev_dbg(pctldev->dev,
			"failed to lookup the default state\n");
	} else {
		if (pinctrl_select_state(pctldev->p,
					 pctldev->hog_default))
			dev_err(pctldev->dev,
				"failed to select default state\n");
	}

	pctldev->hog_sleep =
		pinctrl_lookup_state(pctldev->p,
				     PINCTRL_STATE_SLEEP);
	if (IS_ERR(pctldev->hog_sleep))
		dev_dbg(pctldev->dev,
			"failed to lookup the sleep state\n");

	return 0;
}