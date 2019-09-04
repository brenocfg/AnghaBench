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
struct voice {int dummy; } ;
struct sis7019 {int /*<<< orphan*/  voice_lock; } ;

/* Variables and functions */
 struct voice* __sis_alloc_playback_voice (struct sis7019*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct voice *sis_alloc_playback_voice(struct sis7019 *sis)
{
	struct voice *voice;
	unsigned long flags;

	spin_lock_irqsave(&sis->voice_lock, flags);
	voice = __sis_alloc_playback_voice(sis);
	spin_unlock_irqrestore(&sis->voice_lock, flags);

	return voice;
}