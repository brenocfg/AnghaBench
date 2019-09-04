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
struct ac97_controller_ops {int dummy; } ;
struct ac97_controller {unsigned short slots_available; struct device* parent; struct ac97_controller_ops const* ops; void** codecs_pdata; } ;

/* Variables and functions */
 int AC97_BUS_MAX_CODECS ; 
 int ENOMEM ; 
 struct ac97_controller* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ac97_add_adapter (struct ac97_controller*) ; 
 int /*<<< orphan*/  ac97_bus_reset (struct ac97_controller*) ; 
 int /*<<< orphan*/  ac97_bus_scan (struct ac97_controller*) ; 
 int /*<<< orphan*/  kfree (struct ac97_controller*) ; 
 struct ac97_controller* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ac97_controller *snd_ac97_controller_register(
	const struct ac97_controller_ops *ops, struct device *dev,
	unsigned short slots_available, void **codecs_pdata)
{
	struct ac97_controller *ac97_ctrl;
	int ret, i;

	ac97_ctrl = kzalloc(sizeof(*ac97_ctrl), GFP_KERNEL);
	if (!ac97_ctrl)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < AC97_BUS_MAX_CODECS && codecs_pdata; i++)
		ac97_ctrl->codecs_pdata[i] = codecs_pdata[i];

	ac97_ctrl->ops = ops;
	ac97_ctrl->slots_available = slots_available;
	ac97_ctrl->parent = dev;
	ret = ac97_add_adapter(ac97_ctrl);

	if (ret)
		goto err;
	ac97_bus_reset(ac97_ctrl);
	ac97_bus_scan(ac97_ctrl);

	return ac97_ctrl;
err:
	kfree(ac97_ctrl);
	return ERR_PTR(ret);
}