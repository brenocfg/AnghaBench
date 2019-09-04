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
struct watchdog_device {int dummy; } ;
struct asm9260_wdt_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asm9260_wdt_sys_reset (struct asm9260_wdt_priv*) ; 
 struct asm9260_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int asm9260_restart(struct watchdog_device *wdd, unsigned long action,
			   void *data)
{
	struct asm9260_wdt_priv *priv = watchdog_get_drvdata(wdd);

	asm9260_wdt_sys_reset(priv);

	return 0;
}