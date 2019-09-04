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
typedef  int u8 ;
struct pd_message {int dummy; } ;
struct fusb302_chip {int intr_togdone; int intr_bc_lvl; int intr_comp_chng; int vbus_present; scalar_t__ cc_polarity; int /*<<< orphan*/  lock; int /*<<< orphan*/  tcpm_port; void* cc2; void* cc1; int /*<<< orphan*/  bc_lvl_handler; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_INTERRUPT ; 
 int /*<<< orphan*/  FUSB_REG_INTERRUPTA ; 
 int FUSB_REG_INTERRUPTA_HARDRESET ; 
 int FUSB_REG_INTERRUPTA_HARDSENT ; 
 int FUSB_REG_INTERRUPTA_RETRYFAIL ; 
 int FUSB_REG_INTERRUPTA_TOGDONE ; 
 int FUSB_REG_INTERRUPTA_TX_SUCCESS ; 
 int /*<<< orphan*/  FUSB_REG_INTERRUPTB ; 
 int FUSB_REG_INTERRUPTB_GCRCSENT ; 
 int FUSB_REG_INTERRUPT_BC_LVL ; 
 int FUSB_REG_INTERRUPT_COLLISION ; 
 int FUSB_REG_INTERRUPT_COMP_CHNG ; 
 int FUSB_REG_INTERRUPT_VBUSOK ; 
 int /*<<< orphan*/  FUSB_REG_STATUS0 ; 
 int FUSB_REG_STATUS0_COMP ; 
 int FUSB_REG_STATUS0_VBUSOK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCPC_TX_FAILED ; 
 int /*<<< orphan*/  TCPC_TX_SUCCESS ; 
 void* TYPEC_CC_OPEN ; 
 scalar_t__ TYPEC_POLARITY_CC1 ; 
 int /*<<< orphan*/  T_BC_LVL_DEBOUNCE_DELAY_MS ; 
 int fusb302_handle_togdone (struct fusb302_chip*) ; 
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,...) ; 
 int fusb302_pd_read_message (struct fusb302_chip*,struct pd_message*) ; 
 int fusb302_pd_reset (struct fusb302_chip*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_cc_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_pd_hard_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_pd_transmit_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_vbus_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fusb302_irq_intn(int irq, void *dev_id)
{
	struct fusb302_chip *chip = dev_id;
	int ret = 0;
	u8 interrupt;
	u8 interrupta;
	u8 interruptb;
	u8 status0;
	bool vbus_present;
	bool comp_result;
	bool intr_togdone;
	bool intr_bc_lvl;
	bool intr_comp_chng;
	struct pd_message pd_msg;

	mutex_lock(&chip->lock);
	/* grab a snapshot of intr flags */
	intr_togdone = chip->intr_togdone;
	intr_bc_lvl = chip->intr_bc_lvl;
	intr_comp_chng = chip->intr_comp_chng;

	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPT, &interrupt);
	if (ret < 0)
		goto done;
	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPTA, &interrupta);
	if (ret < 0)
		goto done;
	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPTB, &interruptb);
	if (ret < 0)
		goto done;
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret < 0)
		goto done;
	fusb302_log(chip,
		    "IRQ: 0x%02x, a: 0x%02x, b: 0x%02x, status0: 0x%02x",
		    interrupt, interrupta, interruptb, status0);

	if (interrupt & FUSB_REG_INTERRUPT_VBUSOK) {
		vbus_present = !!(status0 & FUSB_REG_STATUS0_VBUSOK);
		fusb302_log(chip, "IRQ: VBUS_OK, vbus=%s",
			    vbus_present ? "On" : "Off");
		if (vbus_present != chip->vbus_present) {
			chip->vbus_present = vbus_present;
			tcpm_vbus_change(chip->tcpm_port);
		}
	}

	if ((interrupta & FUSB_REG_INTERRUPTA_TOGDONE) && intr_togdone) {
		fusb302_log(chip, "IRQ: TOGDONE");
		ret = fusb302_handle_togdone(chip);
		if (ret < 0) {
			fusb302_log(chip,
				    "handle togdone error, ret=%d", ret);
			goto done;
		}
	}

	if ((interrupt & FUSB_REG_INTERRUPT_BC_LVL) && intr_bc_lvl) {
		fusb302_log(chip, "IRQ: BC_LVL, handler pending");
		/*
		 * as BC_LVL interrupt can be affected by PD activity,
		 * apply delay to for the handler to wait for the PD
		 * signaling to finish.
		 */
		mod_delayed_work(chip->wq, &chip->bc_lvl_handler,
				 msecs_to_jiffies(T_BC_LVL_DEBOUNCE_DELAY_MS));
	}

	if ((interrupt & FUSB_REG_INTERRUPT_COMP_CHNG) && intr_comp_chng) {
		comp_result = !!(status0 & FUSB_REG_STATUS0_COMP);
		fusb302_log(chip, "IRQ: COMP_CHNG, comp=%s",
			    comp_result ? "true" : "false");
		if (comp_result) {
			/* cc level > Rd_threashold, detach */
			if (chip->cc_polarity == TYPEC_POLARITY_CC1)
				chip->cc1 = TYPEC_CC_OPEN;
			else
				chip->cc2 = TYPEC_CC_OPEN;
			tcpm_cc_change(chip->tcpm_port);
		}
	}

	if (interrupt & FUSB_REG_INTERRUPT_COLLISION) {
		fusb302_log(chip, "IRQ: PD collision");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_RETRYFAIL) {
		fusb302_log(chip, "IRQ: PD retry failed");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_HARDSENT) {
		fusb302_log(chip, "IRQ: PD hardreset sent");
		ret = fusb302_pd_reset(chip);
		if (ret < 0) {
			fusb302_log(chip, "cannot PD reset, ret=%d", ret);
			goto done;
		}
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_TX_SUCCESS) {
		fusb302_log(chip, "IRQ: PD tx success");
		ret = fusb302_pd_read_message(chip, &pd_msg);
		if (ret < 0) {
			fusb302_log(chip,
				    "cannot read in PD message, ret=%d", ret);
			goto done;
		}
	}

	if (interrupta & FUSB_REG_INTERRUPTA_HARDRESET) {
		fusb302_log(chip, "IRQ: PD received hardreset");
		ret = fusb302_pd_reset(chip);
		if (ret < 0) {
			fusb302_log(chip, "cannot PD reset, ret=%d", ret);
			goto done;
		}
		tcpm_pd_hard_reset(chip->tcpm_port);
	}

	if (interruptb & FUSB_REG_INTERRUPTB_GCRCSENT) {
		fusb302_log(chip, "IRQ: PD sent good CRC");
		ret = fusb302_pd_read_message(chip, &pd_msg);
		if (ret < 0) {
			fusb302_log(chip,
				    "cannot read in PD message, ret=%d", ret);
			goto done;
		}
	}
done:
	mutex_unlock(&chip->lock);

	return IRQ_HANDLED;
}