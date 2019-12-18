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
typedef  int /*<<< orphan*/  u8 ;
struct midi_runtime {int /*<<< orphan*/  in_lock; scalar_t__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_receive (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void usb6fire_midi_in_received(
		struct midi_runtime *rt, u8 *data, int length)
{
	unsigned long flags;

	spin_lock_irqsave(&rt->in_lock, flags);
	if (rt->in)
		snd_rawmidi_receive(rt->in, data, length);
	spin_unlock_irqrestore(&rt->in_lock, flags);
}