#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  lock; TYPE_1__* card; int /*<<< orphan*/  mmio; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VORTEX_CTRL ; 
 int /*<<< orphan*/  VORTEX_ENGINE_CTRL ; 
 int /*<<< orphan*/  VORTEX_IRQ_SOURCE ; 
 int /*<<< orphan*/  VORTEX_IRQ_STAT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_Vort3D_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_adb_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_adbdma_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_codec_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_eq_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_fifo_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_mixer_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_settimer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vortex_spdif_init (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  vortex_srcblock_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vortex_wt_init (TYPE_2__*) ; 

__attribute__((used)) static int vortex_core_init(vortex_t *vortex)
{

	dev_info(vortex->card->dev, "init started\n");
	/* Hardware Init. */
	hwwrite(vortex->mmio, VORTEX_CTRL, 0xffffffff);
	msleep(5);
	hwwrite(vortex->mmio, VORTEX_CTRL,
		hwread(vortex->mmio, VORTEX_CTRL) & 0xffdfffff);
	msleep(5);
	/* Reset IRQ flags */
	hwwrite(vortex->mmio, VORTEX_IRQ_SOURCE, 0xffffffff);
	hwread(vortex->mmio, VORTEX_IRQ_STAT);

	vortex_codec_init(vortex);

#ifdef CHIP_AU8830
	hwwrite(vortex->mmio, VORTEX_CTRL,
		hwread(vortex->mmio, VORTEX_CTRL) | 0x1000000);
#endif

	/* Init audio engine. */
	vortex_adbdma_init(vortex);
	hwwrite(vortex->mmio, VORTEX_ENGINE_CTRL, 0x0);	//, 0xc83c7e58, 0xc5f93e58
	vortex_adb_init(vortex);
	/* Init processing blocks. */
	vortex_fifo_init(vortex);
	vortex_mixer_init(vortex);
	vortex_srcblock_init(vortex);
#ifndef CHIP_AU8820
	vortex_eq_init(vortex);
	vortex_spdif_init(vortex, 48000, 1);
	vortex_Vort3D_enable(vortex);
#endif
#ifndef CHIP_AU8810
	vortex_wt_init(vortex);
#endif
	// Moved to au88x0.c
	//vortex_connect_default(vortex, 1);

	vortex_settimer(vortex, 0x90);
	// Enable Interrupts.
	// vortex_enable_int() must be first !!
	//  hwwrite(vortex->mmio, VORTEX_IRQ_CTRL, 0);
	// vortex_enable_int(vortex);
	//vortex_enable_timer_int(vortex);
	//vortex_disable_timer_int(vortex);

	dev_info(vortex->card->dev, "init.... done.\n");
	spin_lock_init(&vortex->lock);

	return 0;
}