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
struct snd_interval {unsigned int min; unsigned int max; int openmin; scalar_t__ openmax; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_interval_empty (struct snd_interval*) ; 
 scalar_t__ snd_interval_single (struct snd_interval*) ; 

__attribute__((used)) static int snd_interval_refine_last(struct snd_interval *i)
{
	const unsigned int last_min = i->min;

	if (snd_BUG_ON(snd_interval_empty(i)))
		return -EINVAL;
	if (snd_interval_single(i))
		return 0;
	i->min = i->max;
	if (i->openmax)
		i->min--;
	/* only exclude min value if also excluded before refine */
	i->openmin = (i->openmin && i->min <= last_min);
	return 1;
}