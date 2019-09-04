#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpc8xxx_wdt_ddata {int /*<<< orphan*/  lock; TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  swsrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpc8xxx_wdt_keepalive(struct mpc8xxx_wdt_ddata *ddata)
{
	/* Ping the WDT */
	spin_lock(&ddata->lock);
	out_be16(&ddata->base->swsrr, 0x556c);
	out_be16(&ddata->base->swsrr, 0xaa39);
	spin_unlock(&ddata->lock);
}