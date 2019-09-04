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
struct wm831x_wdt_drvdata {int update_state; int /*<<< orphan*/  lock; scalar_t__ update_gpio; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM831X_WATCHDOG ; 
 int WM831X_WDOG_RESET ; 
 int WM831X_WDOG_RST_SRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm831x_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct wm831x_wdt_drvdata *driver_data = watchdog_get_drvdata(wdt_dev);
	struct wm831x *wm831x = driver_data->wm831x;
	int ret;
	u16 reg;

	mutex_lock(&driver_data->lock);

	if (driver_data->update_gpio) {
		gpio_set_value_cansleep(driver_data->update_gpio,
					driver_data->update_state);
		driver_data->update_state = !driver_data->update_state;
		ret = 0;
		goto out;
	}

	reg = wm831x_reg_read(wm831x, WM831X_WATCHDOG);

	if (!(reg & WM831X_WDOG_RST_SRC)) {
		dev_err(wm831x->dev, "Hardware watchdog update unsupported\n");
		ret = -EINVAL;
		goto out;
	}

	reg |= WM831X_WDOG_RESET;

	ret = wm831x_reg_unlock(wm831x);
	if (ret == 0) {
		ret = wm831x_reg_write(wm831x, WM831X_WATCHDOG, reg);
		wm831x_reg_lock(wm831x);
	} else {
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	}

out:
	mutex_unlock(&driver_data->lock);

	return ret;
}