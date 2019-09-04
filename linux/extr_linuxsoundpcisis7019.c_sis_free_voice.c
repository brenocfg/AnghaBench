#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct voice {int flags; TYPE_1__* timing; } ;
struct sis7019 {int /*<<< orphan*/  voice_lock; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int VOICE_IN_USE ; 
 int VOICE_SSO_TIMING ; 
 int VOICE_SYNC_TIMING ; 
 int /*<<< orphan*/  __sis_unmap_silence (struct sis7019*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sis_free_voice(struct sis7019 *sis, struct voice *voice)
{
	unsigned long flags;

	spin_lock_irqsave(&sis->voice_lock, flags);
	if (voice->timing) {
		__sis_unmap_silence(sis);
		voice->timing->flags &= ~(VOICE_IN_USE | VOICE_SSO_TIMING |
						VOICE_SYNC_TIMING);
		voice->timing = NULL;
	}
	voice->flags &= ~(VOICE_IN_USE | VOICE_SSO_TIMING | VOICE_SYNC_TIMING);
	spin_unlock_irqrestore(&sis->voice_lock, flags);
}