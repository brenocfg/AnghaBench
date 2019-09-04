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
typedef  int u32 ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_cmd52 {int read_write; int address; int data; scalar_t__ raw; scalar_t__ function; } ;
struct TYPE_2__ {int nint; scalar_t__ irq_gpio; scalar_t__ has_thrpt_enh3; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EN_VMM ; 
 int MAX_NUM_INT ; 
 int MAX_NUN_INT_THRPT_ENH2 ; 
 int SEL_VMM_TBL0 ; 
 int SEL_VMM_TBL1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct sdio_func* dev_to_sdio_func (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_sdio ; 
 int wilc_sdio_cmd52 (struct wilc*,struct sdio_cmd52*) ; 

__attribute__((used)) static int sdio_clear_int_ext(struct wilc *wilc, u32 val)
{
	struct sdio_func *func = dev_to_sdio_func(wilc->dev);
	int ret;
	int vmm_ctl;

	if (g_sdio.has_thrpt_enh3) {
		u32 reg;

		if (g_sdio.irq_gpio) {
			u32 flags;

			flags = val & (BIT(MAX_NUN_INT_THRPT_ENH2) - 1);
			reg = flags;
		} else {
			reg = 0;
		}
		/* select VMM table 0 */
		if (val & SEL_VMM_TBL0)
			reg |= BIT(5);
		/* select VMM table 1 */
		if (val & SEL_VMM_TBL1)
			reg |= BIT(6);
		/* enable VMM */
		if (val & EN_VMM)
			reg |= BIT(7);
		if (reg) {
			struct sdio_cmd52 cmd;

			cmd.read_write = 1;
			cmd.function = 0;
			cmd.raw = 0;
			cmd.address = 0xf8;
			cmd.data = reg;

			ret = wilc_sdio_cmd52(wilc, &cmd);
			if (ret) {
				dev_err(&func->dev,
					"Failed cmd52, set 0xf8 data (%d) ...\n",
					__LINE__);
				goto fail;
			}
		}
		return 1;
	}
	if (g_sdio.irq_gpio) {
		/* has_thrpt_enh2 uses register 0xf8 to clear interrupts. */
		/*
		 * Cannot clear multiple interrupts.
		 * Must clear each interrupt individually.
		 */
		u32 flags;

		flags = val & (BIT(MAX_NUM_INT) - 1);
		if (flags) {
			int i;

			ret = 1;
			for (i = 0; i < g_sdio.nint; i++) {
				if (flags & 1) {
					struct sdio_cmd52 cmd;

					cmd.read_write = 1;
					cmd.function = 0;
					cmd.raw = 0;
					cmd.address = 0xf8;
					cmd.data = BIT(i);

					ret = wilc_sdio_cmd52(wilc, &cmd);
					if (ret) {
						dev_err(&func->dev,
							"Failed cmd52, set 0xf8 data (%d) ...\n",
							__LINE__);
						goto fail;
					}
				}
				if (!ret)
					break;
				flags >>= 1;
			}
			if (!ret)
				goto fail;
			for (i = g_sdio.nint; i < MAX_NUM_INT; i++) {
				if (flags & 1)
					dev_err(&func->dev,
						"Unexpected interrupt cleared %d...\n",
						i);
				flags >>= 1;
			}
		}
	}

	vmm_ctl = 0;
	/* select VMM table 0 */
	if (val & SEL_VMM_TBL0)
		vmm_ctl |= BIT(0);
	/* select VMM table 1 */
	if (val & SEL_VMM_TBL1)
		vmm_ctl |= BIT(1);
	/* enable VMM */
	if (val & EN_VMM)
		vmm_ctl |= BIT(2);

	if (vmm_ctl) {
		struct sdio_cmd52 cmd;

		cmd.read_write = 1;
		cmd.function = 0;
		cmd.raw = 0;
		cmd.address = 0xf6;
		cmd.data = vmm_ctl;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		if (ret) {
			dev_err(&func->dev,
				"Failed cmd52, set 0xf6 data (%d) ...\n",
				__LINE__);
			goto fail;
		}
	}
	return 1;
fail:
	return 0;
}