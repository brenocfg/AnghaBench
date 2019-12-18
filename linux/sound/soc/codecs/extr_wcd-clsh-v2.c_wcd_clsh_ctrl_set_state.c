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
struct wcd_clsh_ctrl {int state; int mode; struct snd_soc_component* comp; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum wcd_clsh_mode { ____Placeholder_wcd_clsh_mode } wcd_clsh_mode ;
typedef  enum wcd_clsh_event { ____Placeholder_wcd_clsh_event } wcd_clsh_event ;

/* Variables and functions */
 int /*<<< orphan*/  CLSH_REQ_DISABLE ; 
 int /*<<< orphan*/  CLSH_REQ_ENABLE ; 
 int EINVAL ; 
#define  WCD_CLSH_EVENT_POST_PA 129 
#define  WCD_CLSH_EVENT_PRE_DAC 128 
 int /*<<< orphan*/  _wcd_clsh_ctrl_set_state (struct wcd_clsh_ctrl*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcd_clsh_is_state_valid (int) ; 

int wcd_clsh_ctrl_set_state(struct wcd_clsh_ctrl *ctrl,
			    enum wcd_clsh_event clsh_event,
			    int nstate,
			    enum wcd_clsh_mode mode)
{
	struct snd_soc_component *comp = ctrl->comp;

	if (nstate == ctrl->state)
		return 0;

	if (!wcd_clsh_is_state_valid(nstate)) {
		dev_err(comp->dev, "Class-H not a valid new state:\n");
		return -EINVAL;
	}

	switch (clsh_event) {
	case WCD_CLSH_EVENT_PRE_DAC:
		_wcd_clsh_ctrl_set_state(ctrl, nstate, CLSH_REQ_ENABLE, mode);
		break;
	case WCD_CLSH_EVENT_POST_PA:
		_wcd_clsh_ctrl_set_state(ctrl, nstate, CLSH_REQ_DISABLE, mode);
		break;
	}

	ctrl->state = nstate;
	ctrl->mode = mode;

	return 0;
}