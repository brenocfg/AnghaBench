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
struct wm5100_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WM5100_CLKGEN_ERR_ASYNC_EINT ; 
 int WM5100_CLKGEN_ERR_EINT ; 
 int WM5100_SPK_SHUTDOWN_EINT ; 
 int WM5100_SPK_SHUTDOWN_WARN_EINT ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wm5100_log_status3(struct wm5100_priv *wm5100, int val)
{
	if (val & WM5100_SPK_SHUTDOWN_WARN_EINT)
		dev_crit(wm5100->dev, "Speaker shutdown warning\n");
	if (val & WM5100_SPK_SHUTDOWN_EINT)
		dev_crit(wm5100->dev, "Speaker shutdown\n");
	if (val & WM5100_CLKGEN_ERR_EINT)
		dev_crit(wm5100->dev, "SYSCLK underclocked\n");
	if (val & WM5100_CLKGEN_ERR_ASYNC_EINT)
		dev_crit(wm5100->dev, "ASYNCCLK underclocked\n");
}