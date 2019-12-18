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
struct snd_seq_prioq {int cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

int snd_seq_prioq_avail(struct snd_seq_prioq * f)
{
	if (f == NULL) {
		pr_debug("ALSA: seq: snd_seq_prioq_cell_in() called with NULL prioq\n");
		return 0;
	}
	return f->cells;
}