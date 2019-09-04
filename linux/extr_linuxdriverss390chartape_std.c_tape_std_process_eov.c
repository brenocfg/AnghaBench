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
struct tape_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTBSR ; 
 int /*<<< orphan*/  MTWEOF ; 
 scalar_t__ tape_mtop (struct tape_device*,int /*<<< orphan*/ ,int) ; 

void
tape_std_process_eov(struct tape_device *device)
{
	/*
	 * End of volume: We have to backspace the last written record, then
	 * we TRY to write a tapemark and then backspace over the written TM
	 */
	if (tape_mtop(device, MTBSR, 1) == 0 &&
	    tape_mtop(device, MTWEOF, 1) == 0) {
		tape_mtop(device, MTBSR, 1);
	}
}