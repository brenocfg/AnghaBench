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
struct snd_rawmidi_runtime {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_runtime_ptrs (struct snd_rawmidi_runtime*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void reset_runtime_ptrs(struct snd_rawmidi_runtime *runtime,
			       bool is_input)
{
	unsigned long flags;

	spin_lock_irqsave(&runtime->lock, flags);
	__reset_runtime_ptrs(runtime, is_input);
	spin_unlock_irqrestore(&runtime->lock, flags);
}