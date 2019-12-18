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
struct seq_oss_devinfo {int /*<<< orphan*/  max_mididev; } ;

/* Variables and functions */
 int /*<<< orphan*/  max_midi_devs ; 

void
snd_seq_oss_midi_setup(struct seq_oss_devinfo *dp)
{
	dp->max_mididev = max_midi_devs;
}