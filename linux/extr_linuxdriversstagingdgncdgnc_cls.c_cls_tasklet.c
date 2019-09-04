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
struct dgnc_board {int state; int nasync; int /*<<< orphan*/  bd_intr_lock; struct channel_t** channels; int /*<<< orphan*/  bd_lock; } ;
struct channel_t {scalar_t__ ch_stop_sending_break; } ;

/* Variables and functions */
 int BOARD_READY ; 
 int /*<<< orphan*/  cls_clear_break (struct channel_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cls_copy_data_from_queue_to_uart (struct channel_t*) ; 
 int /*<<< orphan*/  dgnc_carrier (struct channel_t*) ; 
 int /*<<< orphan*/  dgnc_input (struct channel_t*) ; 
 int /*<<< orphan*/  dgnc_wakeup_writes (struct channel_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cls_tasklet(unsigned long data)
{
	struct dgnc_board *bd = (struct dgnc_board *)data;
	struct channel_t *ch;
	unsigned long flags;
	int i;
	int state = 0;
	int ports = 0;

	if (!bd)
		return;

	spin_lock_irqsave(&bd->bd_lock, flags);
	state = bd->state;
	ports = bd->nasync;
	spin_unlock_irqrestore(&bd->bd_lock, flags);

	/*
	 * Do NOT allow the interrupt routine to read the intr registers
	 * Until we release this lock.
	 */
	spin_lock_irqsave(&bd->bd_intr_lock, flags);

	if ((state == BOARD_READY) && (ports > 0)) {
		for (i = 0; i < ports; i++) {
			ch = bd->channels[i];

			/*
			 * NOTE: Remember you CANNOT hold any channel
			 * locks when calling input.
			 * During input processing, its possible we
			 * will call ld, which might do callbacks back
			 * into us.
			 */
			dgnc_input(ch);

			/*
			 * Channel lock is grabbed and then released
			 * inside this routine.
			 */
			cls_copy_data_from_queue_to_uart(ch);
			dgnc_wakeup_writes(ch);

			dgnc_carrier(ch);

			/*
			 * The timing check of turning off the break is done
			 * inside clear_break()
			 */
			if (ch->ch_stop_sending_break)
				cls_clear_break(ch, 0);
		}
	}

	spin_unlock_irqrestore(&bd->bd_intr_lock, flags);
}