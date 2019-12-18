#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int CTRL_IRQ_ENABLE ; 
 int /*<<< orphan*/  VORTEX_CTRL ; 
 int /*<<< orphan*/  VORTEX_IRQ_CTRL ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vortex_enable_int(vortex_t * card)
{
	// CAsp4ISR__EnableVortexInt_void_
	hwwrite(card->mmio, VORTEX_CTRL,
		hwread(card->mmio, VORTEX_CTRL) | CTRL_IRQ_ENABLE);
	hwwrite(card->mmio, VORTEX_IRQ_CTRL,
		(hwread(card->mmio, VORTEX_IRQ_CTRL) & 0xffffefc0) | 0x24);
}