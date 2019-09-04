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
struct tty_struct {int dummy; } ;
struct nozomi {int /*<<< orphan*/  spin_mutex; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 struct nozomi* get_dc_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  set_dtr (struct tty_struct*,int) ; 
 int /*<<< orphan*/  set_rts (struct tty_struct*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ntty_tiocmset(struct tty_struct *tty,
					unsigned int set, unsigned int clear)
{
	struct nozomi *dc = get_dc_by_tty(tty);
	unsigned long flags;

	spin_lock_irqsave(&dc->spin_mutex, flags);
	if (set & TIOCM_RTS)
		set_rts(tty, 1);
	else if (clear & TIOCM_RTS)
		set_rts(tty, 0);

	if (set & TIOCM_DTR)
		set_dtr(tty, 1);
	else if (clear & TIOCM_DTR)
		set_dtr(tty, 0);
	spin_unlock_irqrestore(&dc->spin_mutex, flags);

	return 0;
}