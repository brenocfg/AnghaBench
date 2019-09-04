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
 int /*<<< orphan*/  DBG1 (char*) ; 
 struct nozomi* get_dc_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  set_rts (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ntty_throttle(struct tty_struct *tty)
{
	struct nozomi *dc = get_dc_by_tty(tty);
	unsigned long flags;

	DBG1("THROTTLE");
	spin_lock_irqsave(&dc->spin_mutex, flags);
	set_rts(tty, 0);
	spin_unlock_irqrestore(&dc->spin_mutex, flags);
}