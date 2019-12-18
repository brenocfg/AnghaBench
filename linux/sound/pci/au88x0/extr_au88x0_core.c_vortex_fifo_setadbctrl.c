#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIFO_BITS ; 
 int FIFO_RDONLY ; 
 int /*<<< orphan*/  FIFO_SIZE ; 
 int FIFO_U1 ; 
 int FIFO_VALID ; 
 scalar_t__ VORTEX_FIFO_ADBCTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vortex_fifo_clearadbdata (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_fifo_setadbctrl(vortex_t * vortex, int fifo, int stereo, int priority,
		       int empty, int valid, int f)
{
	int temp, lifeboat = 0;
	//int this_8[NR_ADB] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; /* position */
	int this_4 = 0x2;
	/* f seems priority related.
	 * CAsp4AdbDma::SetPriority is the only place that calls SetAdbCtrl with f set to 1
	 * every where else it is set to 0. It seems, however, that CAsp4AdbDma::SetPriority
	 * is never called, thus the f related bits remain a mystery for now.
	 */
	do {
		temp = hwread(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fifo << 2));
		if (lifeboat++ > 0xbb8) {
			dev_err(vortex->card->dev,
				"vortex_fifo_setadbctrl fail\n");
			break;
		}
	}
	while (temp & FIFO_RDONLY);

	// AU8830 semes to take some special care about fifo content (data).
	// But i'm just to lazy to translate that :)
	if (valid) {
		if ((temp & FIFO_VALID) == 0) {
			//this_8[fifo] = 0;
			vortex_fifo_clearadbdata(vortex, fifo, FIFO_SIZE);	// this_4
#ifdef CHIP_AU8820
			temp = (this_4 & 0x1f) << 0xb;
#else
			temp = (this_4 & 0x3f) << 0xc;
#endif
			temp = (temp & 0xfffffffd) | ((stereo & 1) << 1);
			temp = (temp & 0xfffffff3) | ((priority & 3) << 2);
			temp = (temp & 0xffffffef) | ((valid & 1) << 4);
			temp |= FIFO_U1;
			temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
#ifdef CHIP_AU8820
			temp = (temp & 0xfffbffff) | ((f & 1) << 0x12);
#endif
#ifdef CHIP_AU8830
			temp = (temp & 0xf7ffffff) | ((f & 1) << 0x1b);
			temp = (temp & 0xefffffff) | ((f & 1) << 0x1c);
#endif
#ifdef CHIP_AU8810
			temp = (temp & 0xfeffffff) | ((f & 1) << 0x18);
			temp = (temp & 0xfdffffff) | ((f & 1) << 0x19);
#endif
		}
	} else {
		if (temp & FIFO_VALID) {
#ifdef CHIP_AU8820
			temp = ((f & 1) << 0x12) | (temp & 0xfffbffef);
#endif
#ifdef CHIP_AU8830
			temp =
			    ((f & 1) << 0x1b) | (temp & 0xe7ffffef) | FIFO_BITS;
#endif
#ifdef CHIP_AU8810
			temp =
			    ((f & 1) << 0x18) | (temp & 0xfcffffef) | FIFO_BITS;
#endif
		} else
			/*if (this_8[fifo]) */
			vortex_fifo_clearadbdata(vortex, fifo, FIFO_SIZE);
	}
	hwwrite(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fifo << 2), temp);
	hwread(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fifo << 2));
}