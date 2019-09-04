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
struct TYPE_9__ {int enable_video; int pix_bpp; int video_scale; scalar_t__ pclk_khz; int /*<<< orphan*/  gr_during_vid; } ;
typedef  TYPE_1__ nv3_sim_state ;
struct TYPE_10__ {char valid; int /*<<< orphan*/  video_burst_size; int /*<<< orphan*/  video_lwm; scalar_t__ rtl_values; } ;
typedef  TYPE_2__ nv3_fifo_info ;
struct TYPE_11__ {int gr_en; int vid_en; int vid_only_once; int gr_only_once; int gdrain_rate; int vdrain_rate; int mdrain_rate; char converged; } ;
typedef  TYPE_3__ nv3_arb_info ;

/* Variables and functions */
 char nv3_get_param (TYPE_2__*,TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static void nv3CalcArbitration 
(
    nv3_fifo_info * res_info,
    nv3_sim_state * state
)
{
    nv3_fifo_info save_info;
    nv3_arb_info ainfo;
    char   res_gr, res_vid;

    ainfo.gr_en = 1;
    ainfo.vid_en = state->enable_video;
    ainfo.vid_only_once = 0;
    ainfo.gr_only_once = 0;
    ainfo.gdrain_rate = (int) state->pclk_khz * (state->pix_bpp/8);
    ainfo.vdrain_rate = (int) state->pclk_khz * 2;
    if (state->video_scale != 0)
        ainfo.vdrain_rate = ainfo.vdrain_rate/state->video_scale;
    ainfo.mdrain_rate = 33000;
    res_info->rtl_values = 0;
    if (!state->gr_during_vid && state->enable_video)
    {
        ainfo.gr_only_once = 1;
        ainfo.gr_en = 1;
        ainfo.gdrain_rate = 0;
        res_vid = nv3_get_param(res_info, state,  &ainfo);
        res_vid = ainfo.converged;
        save_info.video_lwm = res_info->video_lwm;
        save_info.video_burst_size = res_info->video_burst_size;
        ainfo.vid_en = 1;
        ainfo.vid_only_once = 1;
        ainfo.gr_en = 1;
        ainfo.gdrain_rate = (int) state->pclk_khz * (state->pix_bpp/8);
        ainfo.vdrain_rate = 0;
        res_gr = nv3_get_param(res_info, state,  &ainfo);
        res_gr = ainfo.converged;
        res_info->video_lwm = save_info.video_lwm;
        res_info->video_burst_size = save_info.video_burst_size;
        res_info->valid = res_gr & res_vid;
    }
    else
    {
        if (!ainfo.gr_en) ainfo.gdrain_rate = 0;
        if (!ainfo.vid_en) ainfo.vdrain_rate = 0;
        res_gr = nv3_get_param(res_info, state,  &ainfo);
        res_info->valid = ainfo.converged;
    }
}