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
struct snd_interval {unsigned int min; unsigned int max; int empty; scalar_t__ openmax; scalar_t__ openmin; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_interval_checkempty (struct snd_interval*) ; 

__attribute__((used)) static int snd_interval_step(struct snd_interval *i, unsigned int step)
{
	unsigned int n;
	int changed = 0;
	n = i->min % step;
	if (n != 0 || i->openmin) {
		i->min += step - n;
		i->openmin = 0;
		changed = 1;
	}
	n = i->max % step;
	if (n != 0 || i->openmax) {
		i->max -= n;
		i->openmax = 0;
		changed = 1;
	}
	if (snd_interval_checkempty(i)) {
		i->empty = 1;
		return -EINVAL;
	}
	return changed;
}