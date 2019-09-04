#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int isvirtual; int /*<<< orphan*/  virtual; void* input_mpu; void* output_mpu; } ;
struct TYPE_6__ {TYPE_1__ midi; } ;
struct TYPE_7__ {TYPE_2__ wavefront; } ;
typedef  TYPE_3__ snd_wavefront_card_t ;

/* Variables and functions */
 void* internal_mpu ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snd_wavefront_midi_enable_virtual (snd_wavefront_card_t *card)

{
	unsigned long flags;

	spin_lock_irqsave (&card->wavefront.midi.virtual, flags);
	card->wavefront.midi.isvirtual = 1;
	card->wavefront.midi.output_mpu = internal_mpu;
	card->wavefront.midi.input_mpu = internal_mpu;
	spin_unlock_irqrestore (&card->wavefront.midi.virtual, flags);
}