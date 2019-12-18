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
struct wm_adsp {int dummy; } ;

/* Variables and functions */
 unsigned int ADSP2_SCRATCH0 ; 
 unsigned int ADSP2_SCRATCH1 ; 
 unsigned int ADSP2_SCRATCH2 ; 
 unsigned int ADSP2_SCRATCH3 ; 
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wm_adsp_read_fw_status (struct wm_adsp*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void wm_adsp2_show_fw_status(struct wm_adsp *dsp)
{
	unsigned int offs[] = {
		ADSP2_SCRATCH0, ADSP2_SCRATCH1, ADSP2_SCRATCH2, ADSP2_SCRATCH3,
	};

	wm_adsp_read_fw_status(dsp, ARRAY_SIZE(offs), offs);

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 offs[0], offs[1], offs[2], offs[3]);
}