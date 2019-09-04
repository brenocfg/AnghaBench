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
struct nvidia_par {int /*<<< orphan*/  PEXTDEV; int /*<<< orphan*/  PFB; } ;
struct TYPE_5__ {char pix_bpp; int enable_video; int memory_type; int memory_width; char mem_latency; int mem_aligned; char mem_page_miss; unsigned int pclk_khz; unsigned int mclk_khz; unsigned int nvclk_khz; scalar_t__ gr_during_vid; scalar_t__ enable_mp; } ;
typedef  TYPE_1__ nv10_sim_state ;
struct TYPE_6__ {int graphics_burst_size; int graphics_lwm; scalar_t__ valid; } ;
typedef  TYPE_2__ nv10_fifo_info ;

/* Variables and functions */
 int NV_RD32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv10CalcArbitration (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nvGetClocks (struct nvidia_par*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void nv10UpdateArbitrationSettings(unsigned VClk,
					  unsigned pixelDepth,
					  unsigned *burst,
					  unsigned *lwm,
					  struct nvidia_par *par)
{
	nv10_fifo_info fifo_data;
	nv10_sim_state sim_data;
	unsigned int MClk, NVClk, cfg1;

	nvGetClocks(par, &MClk, &NVClk);

	cfg1 = NV_RD32(par->PFB, 0x0204);
	sim_data.pix_bpp = (char)pixelDepth;
	sim_data.enable_video = 1;
	sim_data.enable_mp = 0;
	sim_data.memory_type = (NV_RD32(par->PFB, 0x0200) & 0x01) ? 1 : 0;
	sim_data.memory_width = (NV_RD32(par->PEXTDEV, 0x0000) & 0x10) ?
	    128 : 64;
	sim_data.mem_latency = (char)cfg1 & 0x0F;
	sim_data.mem_aligned = 1;
	sim_data.mem_page_miss =
	    (char)(((cfg1 >> 4) & 0x0F) + ((cfg1 >> 31) & 0x01));
	sim_data.gr_during_vid = 0;
	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	nv10CalcArbitration(&fifo_data, &sim_data);
	if (fifo_data.valid) {
		int b = fifo_data.graphics_burst_size >> 4;
		*burst = 0;
		while (b >>= 1)
			(*burst)++;
		*lwm = fifo_data.graphics_lwm >> 3;
	}
}