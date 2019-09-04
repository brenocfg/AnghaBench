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
struct asm9260_wdt_priv {scalar_t__ iobase; int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int BM_MOD_WDEN ; 
 int BM_MOD_WDRESET ; 
 scalar_t__ HW_WDFEED ; 
 scalar_t__ HW_WDMOD ; 
 scalar_t__ HW_WDTC ; 
 int /*<<< orphan*/  asm9260_wdt_feed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void asm9260_wdt_sys_reset(struct asm9260_wdt_priv *priv)
{
	/* init WD if it was not started */

	iowrite32(BM_MOD_WDEN | BM_MOD_WDRESET, priv->iobase + HW_WDMOD);

	iowrite32(0xff, priv->iobase + HW_WDTC);
	/* first pass correct sequence */
	asm9260_wdt_feed(&priv->wdd);
	/*
	 * Then write wrong pattern to the feed to trigger reset
	 * ASAP.
	 */
	iowrite32(0xff, priv->iobase + HW_WDFEED);

	mdelay(1000);
}