#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* card; int /*<<< orphan*/  mmio; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VORTEX_CTRL ; 
 int /*<<< orphan*/  VORTEX_IRQ_CTRL ; 
 int /*<<< orphan*/  VORTEX_IRQ_SOURCE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  vortex_Vort3D_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_adb_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_connect_default (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_disable_int (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_eq_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_fifo_init (TYPE_2__*) ; 

__attribute__((used)) static int vortex_core_shutdown(vortex_t * vortex)
{

	dev_info(vortex->card->dev, "shutdown started\n");
#ifndef CHIP_AU8820
	vortex_eq_free(vortex);
	vortex_Vort3D_disable(vortex);
#endif
	//vortex_disable_timer_int(vortex);
	vortex_disable_int(vortex);
	vortex_connect_default(vortex, 0);
	/* Reset all DMA fifos. */
	vortex_fifo_init(vortex);
	/* Erase all audio routes. */
	vortex_adb_init(vortex);

	/* Disable MPU401 */
	//hwwrite(vortex->mmio, VORTEX_IRQ_CTRL, hwread(vortex->mmio, VORTEX_IRQ_CTRL) & ~IRQ_MIDI);
	//hwwrite(vortex->mmio, VORTEX_CTRL, hwread(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_EN);

	hwwrite(vortex->mmio, VORTEX_IRQ_CTRL, 0);
	hwwrite(vortex->mmio, VORTEX_CTRL, 0);
	msleep(5);
	hwwrite(vortex->mmio, VORTEX_IRQ_SOURCE, 0xffff);

	dev_info(vortex->card->dev, "shutdown.... done.\n");
	return 0;
}