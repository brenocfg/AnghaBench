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
typedef  scalar_t__ u16 ;
struct dwc2_hsotg {scalar_t__ frame_number; scalar_t__ last_frame_num; } ;

/* Variables and functions */
 scalar_t__ dwc2_frame_num_inc (scalar_t__,int) ; 
 int /*<<< orphan*/  dwc2_sch_vdbg (struct dwc2_hsotg*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dwc2_track_missed_sofs(struct dwc2_hsotg *hsotg)
{
	u16 curr_frame_number = hsotg->frame_number;
	u16 expected = dwc2_frame_num_inc(hsotg->last_frame_num, 1);

	if (expected != curr_frame_number)
		dwc2_sch_vdbg(hsotg, "MISSED SOF %04x != %04x\n",
			      expected, curr_frame_number);

#ifdef CONFIG_USB_DWC2_TRACK_MISSED_SOFS
	if (hsotg->frame_num_idx < FRAME_NUM_ARRAY_SIZE) {
		if (expected != curr_frame_number) {
			hsotg->frame_num_array[hsotg->frame_num_idx] =
					curr_frame_number;
			hsotg->last_frame_num_array[hsotg->frame_num_idx] =
					hsotg->last_frame_num;
			hsotg->frame_num_idx++;
		}
	} else if (!hsotg->dumped_frame_num_array) {
		int i;

		dev_info(hsotg->dev, "Frame     Last Frame\n");
		dev_info(hsotg->dev, "-----     ----------\n");
		for (i = 0; i < FRAME_NUM_ARRAY_SIZE; i++) {
			dev_info(hsotg->dev, "0x%04x    0x%04x\n",
				 hsotg->frame_num_array[i],
				 hsotg->last_frame_num_array[i]);
		}
		hsotg->dumped_frame_num_array = 1;
	}
#endif
	hsotg->last_frame_num = curr_frame_number;
}