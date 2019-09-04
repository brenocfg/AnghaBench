#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl_soc_info {int flags; int mux_mask; int mux_shift; TYPE_1__* pins; } ;
struct imx_pinctrl {int base; int input_sel_base; int /*<<< orphan*/  dev; struct imx_pin_reg* pin_regs; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin_reg {int mux_reg; } ;
struct imx_pin {unsigned int pin; int mux_mode; int input_val; int input_reg; } ;
struct group_desc {unsigned int num_pins; int name; scalar_t__ data; } ;
struct function_desc {int name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int SHARE_MUX_CONF_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,unsigned int) ; 
 struct function_desc* pinmux_generic_get_function (struct pinctrl_dev*,unsigned int) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int imx_pmx_set(struct pinctrl_dev *pctldev, unsigned selector,
		       unsigned group)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	const struct imx_pin_reg *pin_reg;
	unsigned int npins, pin_id;
	int i;
	struct group_desc *grp = NULL;
	struct function_desc *func = NULL;

	/*
	 * Configure the mux mode for each pin in the group for a specific
	 * function.
	 */
	grp = pinctrl_generic_get_group(pctldev, group);
	if (!grp)
		return -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	if (!func)
		return -EINVAL;

	npins = grp->num_pins;

	dev_dbg(ipctl->dev, "enable function %s group %s\n",
		func->name, grp->name);

	for (i = 0; i < npins; i++) {
		struct imx_pin *pin = &((struct imx_pin *)(grp->data))[i];

		pin_id = pin->pin;
		pin_reg = &ipctl->pin_regs[pin_id];

		if (pin_reg->mux_reg == -1) {
			dev_dbg(ipctl->dev, "Pin(%s) does not support mux function\n",
				info->pins[pin_id].name);
			continue;
		}

		if (info->flags & SHARE_MUX_CONF_REG) {
			u32 reg;
			reg = readl(ipctl->base + pin_reg->mux_reg);
			reg &= ~info->mux_mask;
			reg |= (pin->mux_mode << info->mux_shift);
			writel(reg, ipctl->base + pin_reg->mux_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
				pin_reg->mux_reg, reg);
		} else {
			writel(pin->mux_mode, ipctl->base + pin_reg->mux_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
				pin_reg->mux_reg, pin->mux_mode);
		}

		/*
		 * If the select input value begins with 0xff, it's a quirky
		 * select input and the value should be interpreted as below.
		 *     31     23      15      7        0
		 *     | 0xff | shift | width | select |
		 * It's used to work around the problem that the select
		 * input for some pin is not implemented in the select
		 * input register but in some general purpose register.
		 * We encode the select input value, width and shift of
		 * the bit field into input_val cell of pin function ID
		 * in device tree, and then decode them here for setting
		 * up the select input bits in general purpose register.
		 */
		if (pin->input_val >> 24 == 0xff) {
			u32 val = pin->input_val;
			u8 select = val & 0xff;
			u8 width = (val >> 8) & 0xff;
			u8 shift = (val >> 16) & 0xff;
			u32 mask = ((1 << width) - 1) << shift;
			/*
			 * The input_reg[i] here is actually some IOMUXC general
			 * purpose register, not regular select input register.
			 */
			val = readl(ipctl->base + pin->input_reg);
			val &= ~mask;
			val |= select << shift;
			writel(val, ipctl->base + pin->input_reg);
		} else if (pin->input_reg) {
			/*
			 * Regular select input register can never be at offset
			 * 0, and we only print register value for regular case.
			 */
			if (ipctl->input_sel_base)
				writel(pin->input_val, ipctl->input_sel_base +
						pin->input_reg);
			else
				writel(pin->input_val, ipctl->base +
						pin->input_reg);
			dev_dbg(ipctl->dev,
				"==>select_input: offset 0x%x val 0x%x\n",
				pin->input_reg, pin->input_val);
		}
	}

	return 0;
}