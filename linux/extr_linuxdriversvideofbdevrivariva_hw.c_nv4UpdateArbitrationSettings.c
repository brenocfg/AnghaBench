#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char pix_bpp; int memory_width; char mem_latency; int mem_aligned; char mem_page_miss; unsigned int pclk_khz; unsigned int mclk_khz; unsigned int nvclk_khz; scalar_t__ gr_during_vid; scalar_t__ enable_mp; scalar_t__ enable_video; } ;
typedef  TYPE_1__ nv4_sim_state ;
struct TYPE_8__ {int graphics_burst_size; int graphics_lwm; scalar_t__ valid; } ;
typedef  TYPE_2__ nv4_fifo_info ;
struct TYPE_9__ {unsigned int CrystalFreqKHz; int /*<<< orphan*/ * PEXTDEV; int /*<<< orphan*/ * PFB; int /*<<< orphan*/ * PRAMDAC0; } ;
typedef  TYPE_3__ RIVA_HW_INST ;

/* Variables and functions */
 int NV_RD32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv4CalcArbitration (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void nv4UpdateArbitrationSettings
(
    unsigned      VClk, 
    unsigned      pixelDepth, 
    unsigned     *burst,
    unsigned     *lwm,
    RIVA_HW_INST *chip
)
{
    nv4_fifo_info fifo_data;
    nv4_sim_state sim_data;
    unsigned int M, N, P, pll, MClk, NVClk, cfg1;

    pll = NV_RD32(&chip->PRAMDAC0[0x00000504/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    MClk  = (N * chip->CrystalFreqKHz / M) >> P;
    pll = NV_RD32(&chip->PRAMDAC0[0x00000500/4], 0);
    M = (pll >> 0)  & 0xFF; N = (pll >> 8)  & 0xFF; P = (pll >> 16) & 0x0F;
    NVClk  = (N * chip->CrystalFreqKHz / M) >> P;
    cfg1 = NV_RD32(&chip->PFB[0x00000204/4], 0);
    sim_data.pix_bpp        = (char)pixelDepth;
    sim_data.enable_video   = 0;
    sim_data.enable_mp      = 0;
    sim_data.memory_width   = (NV_RD32(&chip->PEXTDEV[0x00000000/4], 0) & 0x10) ?
	128 : 64;
    sim_data.mem_latency    = (char)cfg1 & 0x0F;
    sim_data.mem_aligned    = 1;
    sim_data.mem_page_miss  = (char)(((cfg1 >> 4) &0x0F) + ((cfg1 >> 31) & 0x01));
    sim_data.gr_during_vid  = 0;
    sim_data.pclk_khz       = VClk;
    sim_data.mclk_khz       = MClk;
    sim_data.nvclk_khz      = NVClk;
    nv4CalcArbitration(&fifo_data, &sim_data);
    if (fifo_data.valid)
    {
        int  b = fifo_data.graphics_burst_size >> 4;
        *burst = 0;
        while (b >>= 1)
	    (*burst)++;
        *lwm   = fifo_data.graphics_lwm >> 3;
    }
}