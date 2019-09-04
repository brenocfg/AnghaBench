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
struct snd_rme9652 {int running; int /*<<< orphan*/  lock; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_control_register ; 
 int /*<<< orphan*/  RME9652_latency ; 
 int /*<<< orphan*/  rme9652_compute_period_size (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_encode_latency (int) ; 
 int /*<<< orphan*/  rme9652_start (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rme9652_set_interrupt_interval(struct snd_rme9652 *s,
					  unsigned int frames)
{
	int restart = 0;
	int n;

	spin_lock_irq(&s->lock);

	if ((restart = s->running)) {
		rme9652_stop(s);
	}

	frames >>= 7;
	n = 0;
	while (frames) {
		n++;
		frames >>= 1;
	}

	s->control_register &= ~RME9652_latency;
	s->control_register |= rme9652_encode_latency(n);

	rme9652_write(s, RME9652_control_register, s->control_register);

	rme9652_compute_period_size(s);

	if (restart)
		rme9652_start(s);

	spin_unlock_irq(&s->lock);

	return 0;
}