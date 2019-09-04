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
struct TYPE_5__ {int memory_width; int mclk_khz; int mem_page_miss; int /*<<< orphan*/  mem_latency; int /*<<< orphan*/  gr_during_vid; scalar_t__ enable_mp; } ;
typedef  TYPE_1__ nv3_sim_state ;
typedef  int /*<<< orphan*/  nv3_fifo_info ;
struct TYPE_6__ {int cur; int gburst_size; int wcvocc; int vocc; int wcvlwm; int vburst_size; long vdrain_rate; long wcmocc; long mocc; int wcglwm; long wcgocc; long gocc; long gdrain_rate; long by_gfacc; int priority; long mdrain_rate; scalar_t__ converged; int /*<<< orphan*/  first_macc; int /*<<< orphan*/  first_gacc; int /*<<< orphan*/  first_vacc; int /*<<< orphan*/  vid_only_once; scalar_t__ vid_en; int /*<<< orphan*/  gr_only_once; scalar_t__ gr_en; } ;
typedef  TYPE_2__ nv3_arb_info ;

/* Variables and functions */
 int GFIFO_SIZE ; 
 int GFIFO_SIZE_128 ; 
#define  GRAPHICS 129 
 int MFIFO_SIZE ; 
 int MPORT ; 
 int VFIFO_SIZE ; 
#define  VIDEO 128 
 int abs (int) ; 

__attribute__((used)) static int nv3_iterate(nv3_fifo_info *res_info, nv3_sim_state * state, nv3_arb_info *ainfo)
{
    int iter = 0;
    int tmp;
    int vfsize, mfsize, gfsize;
    int mburst_size = 32;
    int mmisses, gmisses, vmisses;
    int misses;
    int vlwm, glwm, mlwm;
    int last, next, cur;
    int max_gfsize ;
    long ns;

    vlwm = 0;
    glwm = 0;
    mlwm = 0;
    vfsize = 0;
    gfsize = 0;
    cur = ainfo->cur;
    mmisses = 2;
    gmisses = 2;
    vmisses = 2;
    if (ainfo->gburst_size == 128) max_gfsize = GFIFO_SIZE_128;
    else  max_gfsize = GFIFO_SIZE;
    max_gfsize = GFIFO_SIZE;
    while (1)
    {
        if (ainfo->vid_en)
        {
            if (ainfo->wcvocc > ainfo->vocc) ainfo->wcvocc = ainfo->vocc;
            if (ainfo->wcvlwm > vlwm) ainfo->wcvlwm = vlwm ;
            ns = 1000000 * ainfo->vburst_size/(state->memory_width/8)/state->mclk_khz;
            vfsize = ns * ainfo->vdrain_rate / 1000000;
            vfsize =  ainfo->wcvlwm - ainfo->vburst_size + vfsize;
        }
        if (state->enable_mp)
        {
            if (ainfo->wcmocc > ainfo->mocc) ainfo->wcmocc = ainfo->mocc;
        }
        if (ainfo->gr_en)
        {
            if (ainfo->wcglwm > glwm) ainfo->wcglwm = glwm ;
            if (ainfo->wcgocc > ainfo->gocc) ainfo->wcgocc = ainfo->gocc;
            ns = 1000000 * (ainfo->gburst_size/(state->memory_width/8))/state->mclk_khz;
            gfsize = (ns * (long) ainfo->gdrain_rate)/1000000;
            gfsize = ainfo->wcglwm - ainfo->gburst_size + gfsize;
        }
        mfsize = 0;
        if (!state->gr_during_vid && ainfo->vid_en)
            if (ainfo->vid_en && (ainfo->vocc < 0) && !ainfo->vid_only_once)
                next = VIDEO;
            else if (ainfo->mocc < 0)
                next = MPORT;
            else if (ainfo->gocc< ainfo->by_gfacc)
                next = GRAPHICS;
            else return (0);
        else switch (ainfo->priority)
            {
                case VIDEO:
                    if (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    else if (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    else if (ainfo->mocc<0)
                        next = MPORT;
                    else    return (0);
                    break;
                case GRAPHICS:
                    if (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    else if (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    else if (ainfo->mocc<0)
                        next = MPORT;
                    else    return (0);
                    break;
                default:
                    if (ainfo->mocc<0)
                        next = MPORT;
                    else if (ainfo->gr_en && ainfo->gocc<0 && !ainfo->gr_only_once)
                        next = GRAPHICS;
                    else if (ainfo->vid_en && ainfo->vocc<0 && !ainfo->vid_only_once)
                        next = VIDEO;
                    else    return (0);
                    break;
            }
        last = cur;
        cur = next;
        iter++;
        switch (cur)
        {
            case VIDEO:
                if (last==cur)    misses = 0;
                else if (ainfo->first_vacc)   misses = vmisses;
                else    misses = 1;
                ainfo->first_vacc = 0;
                if (last!=cur)
                {
                    ns =  1000000 * (vmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz; 
                    vlwm = ns * ainfo->vdrain_rate/ 1000000;
                    vlwm = ainfo->vocc - vlwm;
                }
                ns = 1000000*(misses*state->mem_page_miss + ainfo->vburst_size)/(state->memory_width/8)/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + ainfo->vburst_size - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc - ns*ainfo->mdrain_rate/1000000;
                break;
            case GRAPHICS:
                if (last==cur)    misses = 0;
                else if (ainfo->first_gacc)   misses = gmisses;
                else    misses = 1;
                ainfo->first_gacc = 0;
                if (last!=cur)
                {
                    ns = 1000000*(gmisses*state->mem_page_miss + state->mem_latency)/state->mclk_khz ;
                    glwm = ns * ainfo->gdrain_rate/1000000;
                    glwm = ainfo->gocc - glwm;
                }
                ns = 1000000*(misses*state->mem_page_miss + ainfo->gburst_size/(state->memory_width/8))/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + 0 - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc + ainfo->gburst_size - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc + 0 - ns*ainfo->mdrain_rate/1000000;
                break;
            default:
                if (last==cur)    misses = 0;
                else if (ainfo->first_macc)   misses = mmisses;
                else    misses = 1;
                ainfo->first_macc = 0;
                ns = 1000000*(misses*state->mem_page_miss + mburst_size/(state->memory_width/8))/state->mclk_khz;
                ainfo->vocc = ainfo->vocc + 0 - ns*ainfo->vdrain_rate/1000000;
                ainfo->gocc = ainfo->gocc + 0 - ns*ainfo->gdrain_rate/1000000;
                ainfo->mocc = ainfo->mocc + mburst_size - ns*ainfo->mdrain_rate/1000000;
                break;
        }
        if (iter>100)
        {
            ainfo->converged = 0;
            return (1);
        }
        ns = 1000000*ainfo->gburst_size/(state->memory_width/8)/state->mclk_khz;
        tmp = ns * ainfo->gdrain_rate/1000000;
        if (abs(ainfo->gburst_size) + ((abs(ainfo->wcglwm) + 16 ) & ~0x7) - tmp > max_gfsize)
        {
            ainfo->converged = 0;
            return (1);
        }
        ns = 1000000*ainfo->vburst_size/(state->memory_width/8)/state->mclk_khz;
        tmp = ns * ainfo->vdrain_rate/1000000;
        if (abs(ainfo->vburst_size) + (abs(ainfo->wcvlwm + 32) & ~0xf)  - tmp> VFIFO_SIZE)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(ainfo->gocc) > max_gfsize)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(ainfo->vocc) > VFIFO_SIZE)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(ainfo->mocc) > MFIFO_SIZE)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(vfsize) > VFIFO_SIZE)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(gfsize) > max_gfsize)
        {
            ainfo->converged = 0;
            return (1);
        }
        if (abs(mfsize) > MFIFO_SIZE)
        {
            ainfo->converged = 0;
            return (1);
        }
    }
}