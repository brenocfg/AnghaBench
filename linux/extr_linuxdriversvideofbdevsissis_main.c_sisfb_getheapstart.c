#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct sis_video_info {int sisfb_parm_mem; int video_size; int hwcursor_size; int cmdQueueSize; scalar_t__ sisvga_engine; scalar_t__ cardnumber; scalar_t__ LFBsize; scalar_t__ UMAsize; } ;

/* Variables and functions */
 scalar_t__ SIS_300_VGA ; 

__attribute__((used)) static u32 sisfb_getheapstart(struct sis_video_info *ivideo)
{
	u32 ret = ivideo->sisfb_parm_mem * 1024;
	u32 maxoffs = ivideo->video_size - ivideo->hwcursor_size - ivideo->cmdQueueSize;
	u32 def;

	/* Calculate heap start = end of memory for console
	 *
	 * CCCCCCCCDDDDDDDDDDDDDDDDDDDDDDDDDDDDHHHHQQQQQQQQQQ
	 * C = console, D = heap, H = HWCursor, Q = cmd-queue
	 *
	 * On 76x in UMA+LFB mode, the layout is as follows:
	 * DDDDDDDDDDDCCCCCCCCCCCCCCCCCCCCCCCCHHHHQQQQQQQQQQQ
	 * where the heap is the entire UMA area, eventually
	 * into the LFB area if the given mem parameter is
	 * higher than the size of the UMA memory.
	 *
	 * Basically given by "mem" parameter
	 *
	 * maximum = videosize - cmd_queue - hwcursor
	 *           (results in a heap of size 0)
	 * default = SiS 300: depends on videosize
	 *           SiS 315/330/340/XGI: 32k below max
	 */

	if(ivideo->sisvga_engine == SIS_300_VGA) {
		if(ivideo->video_size > 0x1000000) {
			def = 0xc00000;
		} else if(ivideo->video_size > 0x800000) {
			def = 0x800000;
		} else {
			def = 0x400000;
		}
	} else if(ivideo->UMAsize && ivideo->LFBsize) {
		ret = def = 0;
	} else {
		def = maxoffs - 0x8000;
	}

	/* Use default for secondary card for now (FIXME) */
	if((!ret) || (ret > maxoffs) || (ivideo->cardnumber != 0))
		ret = def;

	return ret;
}