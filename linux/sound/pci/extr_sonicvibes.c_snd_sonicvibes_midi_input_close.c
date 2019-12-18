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
struct sonicvibes {int /*<<< orphan*/  irqmask; } ;
struct snd_mpu401 {struct sonicvibes* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK ; 
 int /*<<< orphan*/  SV_MIDI_MASK ; 
 int /*<<< orphan*/  SV_REG (struct sonicvibes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_sonicvibes_midi_input_close(struct snd_mpu401 * mpu)
{
	struct sonicvibes *sonic = mpu->private_data;
	outb(sonic->irqmask |= SV_MIDI_MASK, SV_REG(sonic, IRQMASK));
}