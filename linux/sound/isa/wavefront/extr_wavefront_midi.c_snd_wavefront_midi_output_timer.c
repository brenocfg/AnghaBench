#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  virtual; int /*<<< orphan*/  timer; int /*<<< orphan*/ * timer_card; } ;
typedef  TYPE_1__ snd_wavefront_midi_t ;
typedef  int /*<<< orphan*/  snd_wavefront_card_t ;

/* Variables and functions */
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_1__* midi ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_wavefront_midi_output_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void snd_wavefront_midi_output_timer(struct timer_list *t)
{
	snd_wavefront_midi_t *midi = from_timer(midi, t, timer);
	snd_wavefront_card_t *card = midi->timer_card;
	unsigned long flags;
	
	spin_lock_irqsave (&midi->virtual, flags);
	mod_timer(&midi->timer, 1 + jiffies);
	spin_unlock_irqrestore (&midi->virtual, flags);
	snd_wavefront_midi_output_write(card);
}