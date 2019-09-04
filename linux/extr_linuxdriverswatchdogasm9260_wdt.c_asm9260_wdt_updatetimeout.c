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
typedef  int u32 ;
struct watchdog_device {int timeout; } ;
struct asm9260_wdt_priv {int wdt_freq; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ HW_WDTC ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct asm9260_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int asm9260_wdt_updatetimeout(struct watchdog_device *wdd)
{
	struct asm9260_wdt_priv *priv = watchdog_get_drvdata(wdd);
	u32 counter;

	counter = wdd->timeout * priv->wdt_freq;

	iowrite32(counter, priv->iobase + HW_WDTC);

	return 0;
}