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
typedef  int u16 ;
struct wm8996_priv {int /*<<< orphan*/  dcs_done; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8996_DC_SERVO_2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_for_dc_servo(struct snd_soc_component *component, u16 mask)
{
	struct i2c_client *i2c = to_i2c_client(component->dev);
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	int ret;
	unsigned long timeout = 200;

	snd_soc_component_write(component, WM8996_DC_SERVO_2, mask);

	/* Use the interrupt if possible */
	do {
		if (i2c->irq) {
			timeout = wait_for_completion_timeout(&wm8996->dcs_done,
							      msecs_to_jiffies(200));
			if (timeout == 0)
				dev_err(component->dev, "DC servo timed out\n");

		} else {
			msleep(1);
			timeout--;
		}

		ret = snd_soc_component_read32(component, WM8996_DC_SERVO_2);
		dev_dbg(component->dev, "DC servo state: %x\n", ret);
	} while (timeout && ret & mask);

	if (timeout == 0)
		dev_err(component->dev, "DC servo timed out for %x\n", mask);
	else
		dev_dbg(component->dev, "DC servo complete for %x\n", mask);
}