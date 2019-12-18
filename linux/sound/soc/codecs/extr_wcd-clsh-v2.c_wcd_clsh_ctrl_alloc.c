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
struct wcd_clsh_ctrl {struct snd_soc_component* comp; int /*<<< orphan*/  state; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct wcd_clsh_ctrl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WCD_CLSH_STATE_IDLE ; 
 struct wcd_clsh_ctrl* kzalloc (int,int /*<<< orphan*/ ) ; 

struct wcd_clsh_ctrl *wcd_clsh_ctrl_alloc(struct snd_soc_component *comp,
					  int version)
{
	struct wcd_clsh_ctrl *ctrl;

	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		return ERR_PTR(-ENOMEM);

	ctrl->state = WCD_CLSH_STATE_IDLE;
	ctrl->comp = comp;

	return ctrl;
}