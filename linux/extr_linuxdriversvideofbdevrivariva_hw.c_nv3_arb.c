#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mclk_khz; int pclk_khz; int memory_width; int mem_page_miss; int mem_latency; scalar_t__ enable_mp; scalar_t__ mem_aligned; } ;
typedef  TYPE_1__ nv3_sim_state ;
struct TYPE_11__ {int graphics_lwm; int video_lwm; long graphics_burst_size; long video_burst_size; int graphics_hi_priority; int media_hi_priority; } ;
typedef  TYPE_2__ nv3_fifo_info ;
struct TYPE_12__ {long by_gfacc; long gdrain_rate; int engine_en; int converged; int mocc; long mdrain_rate; long vocc; long vdrain_rate; long gocc; int first_vacc; int first_gacc; int first_macc; int gburst_size; int vburst_size; scalar_t__ priority; scalar_t__ wcvlwm; scalar_t__ wcglwm; scalar_t__ cur; scalar_t__ gr_en; scalar_t__ vid_en; scalar_t__ wcvocc; scalar_t__ wcgocc; scalar_t__ wcmocc; } ;
typedef  TYPE_3__ nv3_arb_info ;

/* Variables and functions */
 scalar_t__ ENGINE ; 
 scalar_t__ GRAPHICS ; 
 scalar_t__ MPORT ; 
 scalar_t__ VIDEO ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  nv3_iterate (TYPE_2__*,TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static char nv3_arb(nv3_fifo_info * res_info, nv3_sim_state * state,  nv3_arb_info *ainfo) 
{
    long ens, vns, mns, gns;
    int mmisses, gmisses, vmisses, eburst_size, mburst_size;
    int refresh_cycle;

    refresh_cycle = 2*(state->mclk_khz/state->pclk_khz) + 5;
    mmisses = 2;
    if (state->mem_aligned) gmisses = 2;
    else    gmisses = 3;
    vmisses = 2;
    eburst_size = state->memory_width * 1;
    mburst_size = 32;
    gns = 1000000 * (gmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz;
    ainfo->by_gfacc = gns*ainfo->gdrain_rate/1000000;
    ainfo->wcmocc = 0;
    ainfo->wcgocc = 0;
    ainfo->wcvocc = 0;
    ainfo->wcvlwm = 0;
    ainfo->wcglwm = 0;
    ainfo->engine_en = 1;
    ainfo->converged = 1;
    if (ainfo->engine_en)
    {
        ens =  1000000*(state->mem_page_miss + eburst_size/(state->memory_width/8) +refresh_cycle)/state->mclk_khz;
        ainfo->mocc = state->enable_mp ? 0-ens*ainfo->mdrain_rate/1000000 : 0;
        ainfo->vocc = ainfo->vid_en ? 0-ens*ainfo->vdrain_rate/1000000 : 0;
        ainfo->gocc = ainfo->gr_en ? 0-ens*ainfo->gdrain_rate/1000000 : 0;
        ainfo->cur = ENGINE;
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 1;
        nv3_iterate(res_info, state,ainfo);
    }
    if (state->enable_mp)
    {
        mns = 1000000 * (mmisses*state->mem_page_miss + mburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->mocc = state->enable_mp ? 0 : mburst_size - mns*ainfo->mdrain_rate/1000000;
        ainfo->vocc = ainfo->vid_en ? 0 : 0- mns*ainfo->vdrain_rate/1000000;
        ainfo->gocc = ainfo->gr_en ? 0: 0- mns*ainfo->gdrain_rate/1000000;
        ainfo->cur = MPORT;
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 0;
        nv3_iterate(res_info, state,ainfo);
    }
    if (ainfo->gr_en)
    {
        ainfo->first_vacc = 1;
        ainfo->first_gacc = 0;
        ainfo->first_macc = 1;
        gns = 1000000*(gmisses*state->mem_page_miss + ainfo->gburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->gocc = ainfo->gburst_size - gns*ainfo->gdrain_rate/1000000;
        ainfo->vocc = ainfo->vid_en? 0-gns*ainfo->vdrain_rate/1000000 : 0;
        ainfo->mocc = state->enable_mp ?  0-gns*ainfo->mdrain_rate/1000000: 0;
        ainfo->cur = GRAPHICS;
        nv3_iterate(res_info, state,ainfo);
    }
    if (ainfo->vid_en)
    {
        ainfo->first_vacc = 0;
        ainfo->first_gacc = 1;
        ainfo->first_macc = 1;
        vns = 1000000*(vmisses*state->mem_page_miss + ainfo->vburst_size/(state->memory_width/8) + refresh_cycle)/state->mclk_khz;
        ainfo->vocc = ainfo->vburst_size - vns*ainfo->vdrain_rate/1000000;
        ainfo->gocc = ainfo->gr_en? (0-vns*ainfo->gdrain_rate/1000000) : 0;
        ainfo->mocc = state->enable_mp? 0-vns*ainfo->mdrain_rate/1000000 :0 ;
        ainfo->cur = VIDEO;
        nv3_iterate(res_info, state, ainfo);
    }
    if (ainfo->converged)
    {
        res_info->graphics_lwm = (int)abs(ainfo->wcglwm) + 16;
        res_info->video_lwm = (int)abs(ainfo->wcvlwm) + 32;
        res_info->graphics_burst_size = ainfo->gburst_size;
        res_info->video_burst_size = ainfo->vburst_size;
        res_info->graphics_hi_priority = (ainfo->priority == GRAPHICS);
        res_info->media_hi_priority = (ainfo->priority == MPORT);
        if (res_info->video_lwm > 160)
        {
            res_info->graphics_lwm = 256;
            res_info->video_lwm = 128;
            res_info->graphics_burst_size = 64;
            res_info->video_burst_size = 64;
            res_info->graphics_hi_priority = 0;
            res_info->media_hi_priority = 0;
            ainfo->converged = 0;
            return (0);
        }
        if (res_info->video_lwm > 128)
        {
            res_info->video_lwm = 128;
        }
        return (1);
    }
    else
    {
        res_info->graphics_lwm = 256;
        res_info->video_lwm = 128;
        res_info->graphics_burst_size = 64;
        res_info->video_burst_size = 64;
        res_info->graphics_hi_priority = 0;
        res_info->media_hi_priority = 0;
        return (0);
    }
}