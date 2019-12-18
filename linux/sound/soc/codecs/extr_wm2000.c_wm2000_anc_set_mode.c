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
struct wm2000_priv {int /*<<< orphan*/  anc_active; scalar_t__ spk_ena; int /*<<< orphan*/  anc_eng_ena; struct i2c_client* i2c; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum wm2000_anc_mode { ____Placeholder_wm2000_anc_mode } wm2000_anc_mode ;

/* Variables and functions */
 int ANC_ACTIVE ; 
 int ANC_BYPASS ; 
 int ANC_STANDBY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int wm2000_anc_transition (struct wm2000_priv*,int) ; 

__attribute__((used)) static int wm2000_anc_set_mode(struct wm2000_priv *wm2000)
{
	struct i2c_client *i2c = wm2000->i2c;
	enum wm2000_anc_mode mode;

	if (wm2000->anc_eng_ena && wm2000->spk_ena)
		if (wm2000->anc_active)
			mode = ANC_ACTIVE;
		else
			mode = ANC_BYPASS;
	else
		mode = ANC_STANDBY;

	dev_dbg(&i2c->dev, "Set mode %d (enabled %d, mute %d, active %d)\n",
		mode, wm2000->anc_eng_ena, !wm2000->spk_ena,
		wm2000->anc_active);

	return wm2000_anc_transition(wm2000, mode);
}