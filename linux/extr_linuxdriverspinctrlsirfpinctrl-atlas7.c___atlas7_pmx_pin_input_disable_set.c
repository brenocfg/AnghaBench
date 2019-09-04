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
struct atlas7_pmx {scalar_t__* regs; } ;
struct atlas7_pad_mux {int dinput_bit; int dinput_val_bit; scalar_t__ dinput_val_reg; scalar_t__ dinput_reg; } ;

/* Variables and functions */
 size_t BANK_DS ; 
 scalar_t__ CLR_REG (scalar_t__) ; 
 int DIV_DISABLE ; 
 int DIV_MASK ; 
 int DI_DISABLE ; 
 int DI_MASK ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void __atlas7_pmx_pin_input_disable_set(struct atlas7_pmx *pmx,
				const struct atlas7_pad_mux *mux)
{
	/* Set Input Disable to avoid input glitches
	 *
	 * All Input-Disable Control registers are located on IOCRTC.
	 * So the regs bank is always 0.
	 *
	 */
	if (mux->dinput_reg && mux->dinput_val_reg) {
		writel(DI_MASK << mux->dinput_bit,
			pmx->regs[BANK_DS] + CLR_REG(mux->dinput_reg));
		writel(DI_DISABLE << mux->dinput_bit,
			pmx->regs[BANK_DS] + mux->dinput_reg);


		writel(DIV_MASK << mux->dinput_val_bit,
			pmx->regs[BANK_DS] + CLR_REG(mux->dinput_val_reg));
		writel(DIV_DISABLE << mux->dinput_val_bit,
			pmx->regs[BANK_DS] + mux->dinput_val_reg);
	}
}