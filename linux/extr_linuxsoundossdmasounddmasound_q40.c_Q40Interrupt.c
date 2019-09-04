#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  action_queue; int /*<<< orphan*/  count; scalar_t__ active; int /*<<< orphan*/  sync_queue; } ;

/* Variables and functions */
 int* DAC_LEFT ; 
 int* DAC_RIGHT ; 
 int /*<<< orphan*/  Q40Play () ; 
 int /*<<< orphan*/  SAMPLE_CLEAR_REG ; 
 int /*<<< orphan*/  SAMPLE_ENABLE_REG ; 
 int /*<<< orphan*/  WAKE_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int q40_sc ; 
 TYPE_1__ write_sq ; 

__attribute__((used)) static void Q40Interrupt(void)
{
	if (!write_sq.active) {
	          /* playing was interrupted and sq_reset() has already cleared
		   * the sq variables, so better don't do anything here.
		   */
	           WAKE_UP(write_sq.sync_queue);
		   master_outb(0,SAMPLE_ENABLE_REG); /* better safe */
		   goto exit;
	} else write_sq.active=0;
	write_sq.count--;
	Q40Play();

	if (q40_sc<2)
	      { /* there was nothing to play, disable irq */
		master_outb(0,SAMPLE_ENABLE_REG);
		*DAC_LEFT=*DAC_RIGHT=127;
	      }
	WAKE_UP(write_sq.action_queue);

 exit:
	master_outb(1,SAMPLE_CLEAR_REG);
}