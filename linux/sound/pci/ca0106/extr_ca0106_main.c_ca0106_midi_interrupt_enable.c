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
struct snd_ca_midi {scalar_t__ dev_id; } ;
struct snd_ca0106 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ca0106_intr_enable (struct snd_ca0106*,int) ; 

__attribute__((used)) static void ca0106_midi_interrupt_enable(struct snd_ca_midi *midi, int intr)
{
	snd_ca0106_intr_enable((struct snd_ca0106 *)(midi->dev_id), intr);
}