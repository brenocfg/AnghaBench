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
struct wm2000_priv {scalar_t__ anc_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ANC_ACTIVE ; 
 scalar_t__ ANC_STANDBY ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WM2000_ANC_ENG_IDLE ; 
 int WM2000_MODE_ANA_SEQ_INCLUDE ; 
 int WM2000_MODE_STANDBY_ENTRY ; 
 int WM2000_MODE_THERMAL_ENABLE ; 
 int WM2000_RAM_CLR ; 
 int /*<<< orphan*/  WM2000_REG_ANA_VMID_PD_TIME ; 
 int /*<<< orphan*/  WM2000_REG_ANC_STAT ; 
 int /*<<< orphan*/  WM2000_REG_SYS_CTL1 ; 
 int /*<<< orphan*/  WM2000_REG_SYS_CTL2 ; 
 int /*<<< orphan*/  WM2000_REG_SYS_MODE_CNTRL ; 
 int /*<<< orphan*/  WM2000_REG_SYS_STATUS ; 
 int /*<<< orphan*/  WM2000_STATUS_ANC_DISABLED ; 
 int WM2000_SYS_STBY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct wm2000_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm2000_poll_bit (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm2000_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm2000_enter_standby(struct i2c_client *i2c, int analogue)
{
	struct wm2000_priv *wm2000 = dev_get_drvdata(&i2c->dev);

	if (WARN_ON(wm2000->anc_mode != ANC_ACTIVE))
		return -EINVAL;

	if (analogue) {
		wm2000_write(i2c, WM2000_REG_ANA_VMID_PD_TIME, 248 / 4);

		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_ANA_SEQ_INCLUDE |
			     WM2000_MODE_THERMAL_ENABLE |
			     WM2000_MODE_STANDBY_ENTRY);
	} else {
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_THERMAL_ENABLE |
			     WM2000_MODE_STANDBY_ENTRY);
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_SYS_STATUS,
			     WM2000_STATUS_ANC_DISABLED)) {
		dev_err(&i2c->dev,
			"Timed out waiting for ANC disable after 1ms\n");
		return -ETIMEDOUT;
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_ANC_STAT, WM2000_ANC_ENG_IDLE)) {
		dev_err(&i2c->dev,
			"Timed out waiting for standby\n");
		return -ETIMEDOUT;
	}

	wm2000_write(i2c, WM2000_REG_SYS_CTL1, WM2000_SYS_STBY);
	wm2000_write(i2c, WM2000_REG_SYS_CTL2, WM2000_RAM_CLR);

	wm2000->anc_mode = ANC_STANDBY;
	dev_dbg(&i2c->dev, "standby\n");
	if (analogue)
		dev_dbg(&i2c->dev, "Analogue disabled\n");

	return 0;
}