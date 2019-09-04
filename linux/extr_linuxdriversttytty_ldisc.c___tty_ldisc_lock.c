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
struct tty_struct {int /*<<< orphan*/  ldisc_sem; } ;

/* Variables and functions */
 int ldsem_down_write (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int
__tty_ldisc_lock(struct tty_struct *tty, unsigned long timeout)
{
	return ldsem_down_write(&tty->ldisc_sem, timeout);
}