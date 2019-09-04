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
struct TYPE_2__ {int flags; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; scalar_t__ tx_enabled; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HDLC_FLAG_HDLC_LOOPMODE ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_loopmode_insert_request (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_start_transmitter (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static int mgsl_txenable(struct mgsl_struct * info, int enable)
{
 	unsigned long flags;
 
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_txenable(%s,%d)\n", __FILE__,__LINE__,
			info->device_name, enable);
			
	spin_lock_irqsave(&info->irq_spinlock,flags);
	if ( enable ) {
		if ( !info->tx_enabled ) {

			usc_start_transmitter(info);
			/*--------------------------------------------------
			 * if HDLC/SDLC Loop mode, attempt to insert the
			 * station in the 'loop' by setting CMR:13. Upon
			 * receipt of the next GoAhead (RxAbort) sequence,
			 * the OnLoop indicator (CCSR:7) should go active
			 * to indicate that we are on the loop
			 *--------------------------------------------------*/
			if ( info->params.flags & HDLC_FLAG_HDLC_LOOPMODE )
				usc_loopmode_insert_request( info );
		}
	} else {
		if ( info->tx_enabled )
			usc_stop_transmitter(info);
	}
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	return 0;
	
}