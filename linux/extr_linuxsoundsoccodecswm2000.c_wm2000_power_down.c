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
struct wm2000_priv {int /*<<< orphan*/  anc_mode; int /*<<< orphan*/  supplies; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANC_OFF ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WM2000_ANC_ENG_IDLE ; 
 int WM2000_MODE_ANA_SEQ_INCLUDE ; 
 int WM2000_MODE_POWER_DOWN ; 
 int /*<<< orphan*/  WM2000_NUM_SUPPLIES ; 
 int /*<<< orphan*/  WM2000_REG_ANA_VMID_PD_TIME ; 
 int /*<<< orphan*/  WM2000_REG_ANC_STAT ; 
 int /*<<< orphan*/  WM2000_REG_SYS_MODE_CNTRL ; 
 int /*<<< orphan*/  WM2000_REG_SYS_STATUS ; 
 int /*<<< orphan*/  WM2000_STATUS_POWER_DOWN_COMPLETE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct wm2000_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm2000_poll_bit (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm2000_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm2000_power_down(struct i2c_client *i2c, int analogue)
{
	struct wm2000_priv *wm2000 = dev_get_drvdata(&i2c->dev);

	if (analogue) {
		wm2000_write(i2c, WM2000_REG_ANA_VMID_PD_TIME, 248 / 4);
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_ANA_SEQ_INCLUDE |
			     WM2000_MODE_POWER_DOWN);
	} else {
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_POWER_DOWN);
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_SYS_STATUS,
			     WM2000_STATUS_POWER_DOWN_COMPLETE)) {
		dev_err(&i2c->dev, "Timeout waiting for ANC power down\n");
		return -ETIMEDOUT;
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_ANC_STAT,
			     WM2000_ANC_ENG_IDLE)) {
		dev_err(&i2c->dev, "Timeout waiting for ANC engine idle\n");
		return -ETIMEDOUT;
	}

	regulator_bulk_disable(WM2000_NUM_SUPPLIES, wm2000->supplies);

	dev_dbg(&i2c->dev, "powered off\n");
	wm2000->anc_mode = ANC_OFF;

	return 0;
}