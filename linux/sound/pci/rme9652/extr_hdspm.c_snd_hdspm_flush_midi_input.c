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
struct hdspm {int dummy; } ;

/* Variables and functions */
 scalar_t__ snd_hdspm_midi_input_available (struct hdspm*,int) ; 
 int /*<<< orphan*/  snd_hdspm_midi_read_byte (struct hdspm*,int) ; 

__attribute__((used)) static void snd_hdspm_flush_midi_input(struct hdspm *hdspm, int id)
{
	while (snd_hdspm_midi_input_available (hdspm, id))
		snd_hdspm_midi_read_byte (hdspm, id);
}