#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct clk_init_data* init; } ;
struct TYPE_7__ {TYPE_4__ hw; int /*<<< orphan*/ * table; int /*<<< orphan*/ * lock; scalar_t__ flags; scalar_t__ mask; int /*<<< orphan*/  shift; scalar_t__ reg; } ;
struct meson_pwm_channel {int /*<<< orphan*/ * clk_parent; int /*<<< orphan*/ * clk; TYPE_3__ mux; } ;
struct TYPE_5__ {unsigned int npwm; struct device* dev; } ;
struct meson_pwm {int /*<<< orphan*/  lock; scalar_t__ base; TYPE_2__* data; TYPE_1__ chip; } ;
struct device {int dummy; } ;
struct clk_init_data {char* name; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_IS_BASIC ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MISC_CLK_SEL_WIDTH ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_MISC_AB ; 
 int /*<<< orphan*/  clk_mux_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_clk_register (struct device*,TYPE_4__*) ; 
 int /*<<< orphan*/ * mux_reg_shifts ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int meson_pwm_init_channels(struct meson_pwm *meson,
				   struct meson_pwm_channel *channels)
{
	struct device *dev = meson->chip.dev;
	struct clk_init_data init;
	unsigned int i;
	char name[255];
	int err;

	for (i = 0; i < meson->chip.npwm; i++) {
		struct meson_pwm_channel *channel = &channels[i];

		snprintf(name, sizeof(name), "%s#mux%u", dev_name(dev), i);

		init.name = name;
		init.ops = &clk_mux_ops;
		init.flags = CLK_IS_BASIC;
		init.parent_names = meson->data->parent_names;
		init.num_parents = meson->data->num_parents;

		channel->mux.reg = meson->base + REG_MISC_AB;
		channel->mux.shift = mux_reg_shifts[i];
		channel->mux.mask = BIT(MISC_CLK_SEL_WIDTH) - 1;
		channel->mux.flags = 0;
		channel->mux.lock = &meson->lock;
		channel->mux.table = NULL;
		channel->mux.hw.init = &init;

		channel->clk = devm_clk_register(dev, &channel->mux.hw);
		if (IS_ERR(channel->clk)) {
			err = PTR_ERR(channel->clk);
			dev_err(dev, "failed to register %s: %d\n", name, err);
			return err;
		}

		snprintf(name, sizeof(name), "clkin%u", i);

		channel->clk_parent = devm_clk_get(dev, name);
		if (IS_ERR(channel->clk_parent)) {
			err = PTR_ERR(channel->clk_parent);
			if (err == -EPROBE_DEFER)
				return err;

			channel->clk_parent = NULL;
		}
	}

	return 0;
}