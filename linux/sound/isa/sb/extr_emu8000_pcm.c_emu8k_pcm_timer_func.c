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
struct timer_list {int dummy; } ;
struct snd_emu8k_pcm {int last_ptr; int buf_size; int period_pos; int period_size; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  substream; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int emu8k_get_curpos (struct snd_emu8k_pcm*,int /*<<< orphan*/ ) ; 
 struct snd_emu8k_pcm* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct snd_emu8k_pcm* rec ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void emu8k_pcm_timer_func(struct timer_list *t)
{
	struct snd_emu8k_pcm *rec = from_timer(rec, t, timer);
	int ptr, delta;

	spin_lock(&rec->timer_lock);
	/* update the current pointer */
	ptr = emu8k_get_curpos(rec, 0);
	if (ptr < rec->last_ptr)
		delta = ptr + rec->buf_size - rec->last_ptr;
	else
		delta = ptr - rec->last_ptr;
	rec->period_pos += delta;
	rec->last_ptr = ptr;

	/* reprogram timer */
	mod_timer(&rec->timer, jiffies + 1);

	/* update period */
	if (rec->period_pos >= (int)rec->period_size) {
		rec->period_pos %= rec->period_size;
		spin_unlock(&rec->timer_lock);
		snd_pcm_period_elapsed(rec->substream);
		return;
	}
	spin_unlock(&rec->timer_lock);
}