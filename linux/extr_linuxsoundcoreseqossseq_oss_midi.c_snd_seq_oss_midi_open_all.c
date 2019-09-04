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
struct seq_oss_devinfo {int max_mididev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_oss_midi_open (struct seq_oss_devinfo*,int,int) ; 

void
snd_seq_oss_midi_open_all(struct seq_oss_devinfo *dp, int file_mode)
{
	int i;
	for (i = 0; i < dp->max_mididev; i++)
		snd_seq_oss_midi_open(dp, i, file_mode);
}