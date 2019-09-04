#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct skl_module_iface {TYPE_2__* outputs; TYPE_1__* inputs; } ;
struct skl_module_fmt {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct skl_module_fmt fmt; } ;
struct TYPE_3__ {struct skl_module_fmt fmt; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_DIR_IN 129 
#define  SKL_DIR_OUT 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int skl_tplg_fill_fmt (struct device*,struct skl_module_fmt*,int,int) ; 

__attribute__((used)) static int skl_tplg_widget_fill_fmt(struct device *dev,
		struct skl_module_iface *fmt,
		u32 tkn, u32 val, u32 dir, int fmt_idx)
{
	struct skl_module_fmt *dst_fmt;

	if (!fmt)
		return -EINVAL;

	switch (dir) {
	case SKL_DIR_IN:
		dst_fmt = &fmt->inputs[fmt_idx].fmt;
		break;

	case SKL_DIR_OUT:
		dst_fmt = &fmt->outputs[fmt_idx].fmt;
		break;

	default:
		dev_err(dev, "Invalid direction: %d\n", dir);
		return -EINVAL;
	}

	return skl_tplg_fill_fmt(dev, dst_fmt, tkn, val);
}