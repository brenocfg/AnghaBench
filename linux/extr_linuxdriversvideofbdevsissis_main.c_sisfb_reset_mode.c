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
struct sis_video_info {int /*<<< orphan*/  current_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  sisfb_set_base_CRT1 (struct sis_video_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisfb_set_base_CRT2 (struct sis_video_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ sisfb_set_mode (struct sis_video_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisfb_set_pitch (struct sis_video_info*) ; 

__attribute__((used)) static int
sisfb_reset_mode(struct sis_video_info *ivideo)
{
	if(sisfb_set_mode(ivideo, 0))
		return 1;

	sisfb_set_pitch(ivideo);
	sisfb_set_base_CRT1(ivideo, ivideo->current_base);
	sisfb_set_base_CRT2(ivideo, ivideo->current_base);

	return 0;
}