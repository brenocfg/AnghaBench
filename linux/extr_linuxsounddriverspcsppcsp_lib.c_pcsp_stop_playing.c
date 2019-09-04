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
struct snd_pcsp {int val61; int /*<<< orphan*/  timer_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8253_lock ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcsp_stop_playing(struct snd_pcsp *chip)
{
#if PCSP_DEBUG
	printk(KERN_INFO "PCSP: stop_playing called\n");
#endif
	if (!atomic_read(&chip->timer_active))
		return;

	atomic_set(&chip->timer_active, 0);
	raw_spin_lock(&i8253_lock);
	/* restore the timer */
	outb_p(0xb6, 0x43);	/* binary, mode 3, LSB/MSB, ch 2 */
	outb(chip->val61 & 0xFC, 0x61);
	raw_spin_unlock(&i8253_lock);
}