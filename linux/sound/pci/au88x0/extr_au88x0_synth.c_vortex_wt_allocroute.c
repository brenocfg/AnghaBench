#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int parm0; int parm1; } ;
typedef  TYPE_2__ wt_voice_t ;
struct TYPE_11__ {int /*<<< orphan*/  mmio; TYPE_1__* card; TYPE_2__* wt_voice; } ;
typedef  TYPE_3__ vortex_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WT_DELAY (int,int) ; 
 int /*<<< orphan*/  WT_GMODE (int) ; 
 int /*<<< orphan*/  WT_PARM (int,int) ; 
 int /*<<< orphan*/  WT_SRAMP (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vortex_fifo_setwtvalid (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  vortex_fifo_wtinitialize (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  vortex_wt_setdsout (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  vortex_wt_setstereo (TYPE_3__*,int,int) ; 

__attribute__((used)) static int vortex_wt_allocroute(vortex_t * vortex, int wt, int nr_ch)
{
	wt_voice_t *voice = &(vortex->wt_voice[wt]);
	int temp;

	//FIXME: WT audio routing.
	if (nr_ch) {
		vortex_fifo_wtinitialize(vortex, wt, 1);
		vortex_fifo_setwtvalid(vortex, wt, 1);
		vortex_wt_setstereo(vortex, wt, nr_ch - 1);
	} else
		vortex_fifo_setwtvalid(vortex, wt, 0);
	
	/* Set mixdown mode. */
	vortex_wt_setdsout(vortex, wt, 1);
	/* Set other parameter registers. */
	hwwrite(vortex->mmio, WT_SRAMP(0), 0x880000);
	//hwwrite(vortex->mmio, WT_GMODE(0), 0xffffffff);
#ifdef CHIP_AU8830
	hwwrite(vortex->mmio, WT_SRAMP(1), 0x880000);
	//hwwrite(vortex->mmio, WT_GMODE(1), 0xffffffff);
#endif
	hwwrite(vortex->mmio, WT_PARM(wt, 0), 0);
	hwwrite(vortex->mmio, WT_PARM(wt, 1), 0);
	hwwrite(vortex->mmio, WT_PARM(wt, 2), 0);

	temp = hwread(vortex->mmio, WT_PARM(wt, 3));
	dev_dbg(vortex->card->dev, "WT PARM3: %x\n", temp);
	//hwwrite(vortex->mmio, WT_PARM(wt, 3), temp);

	hwwrite(vortex->mmio, WT_DELAY(wt, 0), 0);
	hwwrite(vortex->mmio, WT_DELAY(wt, 1), 0);
	hwwrite(vortex->mmio, WT_DELAY(wt, 2), 0);
	hwwrite(vortex->mmio, WT_DELAY(wt, 3), 0);

	dev_dbg(vortex->card->dev, "WT GMODE: %x\n",
		hwread(vortex->mmio, WT_GMODE(wt)));

	hwwrite(vortex->mmio, WT_PARM(wt, 2), 0xffffffff);
	hwwrite(vortex->mmio, WT_PARM(wt, 3), 0xcff1c810);

	voice->parm0 = voice->parm1 = 0xcfb23e2f;
	hwwrite(vortex->mmio, WT_PARM(wt, 0), voice->parm0);
	hwwrite(vortex->mmio, WT_PARM(wt, 1), voice->parm1);
	dev_dbg(vortex->card->dev, "WT GMODE 2 : %x\n",
		hwread(vortex->mmio, WT_GMODE(wt)));
	return 0;
}