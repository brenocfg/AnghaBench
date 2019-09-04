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
struct tps65217_bl {int is_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  tps; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_WLEDCTRL1 ; 
 int /*<<< orphan*/  TPS65217_WLEDCTRL1_ISINK_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps65217_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65217_bl_enable(struct tps65217_bl *tps65217_bl)
{
	int rc;

	rc = tps65217_set_bits(tps65217_bl->tps, TPS65217_REG_WLEDCTRL1,
			TPS65217_WLEDCTRL1_ISINK_ENABLE,
			TPS65217_WLEDCTRL1_ISINK_ENABLE, TPS65217_PROTECT_NONE);
	if (rc) {
		dev_err(tps65217_bl->dev,
			"failed to enable backlight: %d\n", rc);
		return rc;
	}

	tps65217_bl->is_enabled = true;

	dev_dbg(tps65217_bl->dev, "backlight enabled\n");

	return 0;
}