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
struct TYPE_5__ {int pclk_khz; int mclk_khz; int nvclk_khz; int mem_page_miss; int mem_latency; int memory_width; int enable_video; int pix_bpp; int enable_mp; } ;
typedef  TYPE_1__ nv4_sim_state ;
struct TYPE_6__ {int valid; int graphics_lwm; int graphics_burst_size; int video_lwm; int video_burst_size; } ;
typedef  TYPE_2__ nv4_fifo_info ;

/* Variables and functions */

__attribute__((used)) static void nv4CalcArbitration(nv4_fifo_info * fifo, nv4_sim_state * arb)
{
	int data, pagemiss, cas, width, video_enable, bpp;
	int nvclks, mclks, pclks, vpagemiss, crtpagemiss, vbs;
	int found, mclk_extra, mclk_loop, cbs, m1, p1;
	int mclk_freq, pclk_freq, nvclk_freq, mp_enable;
	int us_m, us_n, us_p, video_drain_rate, crtc_drain_rate;
	int vpm_us, us_video, vlwm, video_fill_us, cpm_us, us_crt, clwm;

	fifo->valid = 1;
	pclk_freq = arb->pclk_khz;
	mclk_freq = arb->mclk_khz;
	nvclk_freq = arb->nvclk_khz;
	pagemiss = arb->mem_page_miss;
	cas = arb->mem_latency;
	width = arb->memory_width >> 6;
	video_enable = arb->enable_video;
	bpp = arb->pix_bpp;
	mp_enable = arb->enable_mp;
	clwm = 0;
	vlwm = 0;
	cbs = 128;
	pclks = 2;
	nvclks = 2;
	nvclks += 2;
	nvclks += 1;
	mclks = 5;
	mclks += 3;
	mclks += 1;
	mclks += cas;
	mclks += 1;
	mclks += 1;
	mclks += 1;
	mclks += 1;
	mclk_extra = 3;
	nvclks += 2;
	nvclks += 1;
	nvclks += 1;
	nvclks += 1;
	if (mp_enable)
		mclks += 4;
	nvclks += 0;
	pclks += 0;
	found = 0;
	vbs = 0;
	while (found != 1) {
		fifo->valid = 1;
		found = 1;
		mclk_loop = mclks + mclk_extra;
		us_m = mclk_loop * 1000 * 1000 / mclk_freq;
		us_n = nvclks * 1000 * 1000 / nvclk_freq;
		us_p = nvclks * 1000 * 1000 / pclk_freq;
		if (video_enable) {
			video_drain_rate = pclk_freq * 2;
			crtc_drain_rate = pclk_freq * bpp / 8;
			vpagemiss = 2;
			vpagemiss += 1;
			crtpagemiss = 2;
			vpm_us =
			    (vpagemiss * pagemiss) * 1000 * 1000 / mclk_freq;
			if (nvclk_freq * 2 > mclk_freq * width)
				video_fill_us =
				    cbs * 1000 * 1000 / 16 / nvclk_freq;
			else
				video_fill_us =
				    cbs * 1000 * 1000 / (8 * width) /
				    mclk_freq;
			us_video = vpm_us + us_m + us_n + us_p + video_fill_us;
			vlwm = us_video * video_drain_rate / (1000 * 1000);
			vlwm++;
			vbs = 128;
			if (vlwm > 128)
				vbs = 64;
			if (vlwm > (256 - 64))
				vbs = 32;
			if (nvclk_freq * 2 > mclk_freq * width)
				video_fill_us =
				    vbs * 1000 * 1000 / 16 / nvclk_freq;
			else
				video_fill_us =
				    vbs * 1000 * 1000 / (8 * width) /
				    mclk_freq;
			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			us_crt =
			    us_video + video_fill_us + cpm_us + us_m + us_n +
			    us_p;
			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			clwm++;
		} else {
			crtc_drain_rate = pclk_freq * bpp / 8;
			crtpagemiss = 2;
			crtpagemiss += 1;
			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			us_crt = cpm_us + us_m + us_n + us_p;
			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			clwm++;
		}
		m1 = clwm + cbs - 512;
		p1 = m1 * pclk_freq / mclk_freq;
		p1 = p1 * bpp / 8;
		if ((p1 < m1) && (m1 > 0)) {
			fifo->valid = 0;
			found = 0;
			if (mclk_extra == 0)
				found = 1;
			mclk_extra--;
		} else if (video_enable) {
			if ((clwm > 511) || (vlwm > 255)) {
				fifo->valid = 0;
				found = 0;
				if (mclk_extra == 0)
					found = 1;
				mclk_extra--;
			}
		} else {
			if (clwm > 519) {
				fifo->valid = 0;
				found = 0;
				if (mclk_extra == 0)
					found = 1;
				mclk_extra--;
			}
		}
		if (clwm < 384)
			clwm = 384;
		if (vlwm < 128)
			vlwm = 128;
		data = (int)(clwm);
		fifo->graphics_lwm = data;
		fifo->graphics_burst_size = 128;
		data = (int)((vlwm + 15));
		fifo->video_lwm = data;
		fifo->video_burst_size = vbs;
	}
}