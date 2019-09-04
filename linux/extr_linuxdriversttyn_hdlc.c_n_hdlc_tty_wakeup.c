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
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct n_hdlc {struct tty_struct* tty; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ debuglevel ; 
 int /*<<< orphan*/  n_hdlc_send_frames (struct n_hdlc*,struct tty_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 struct n_hdlc* tty2n_hdlc (struct tty_struct*) ; 

__attribute__((used)) static void n_hdlc_tty_wakeup(struct tty_struct *tty)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc(tty);

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_tty_wakeup() called\n",__FILE__,__LINE__);
		
	if (!n_hdlc)
		return;

	if (tty != n_hdlc->tty) {
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		return;
	}

	n_hdlc_send_frames (n_hdlc, tty);
		
}