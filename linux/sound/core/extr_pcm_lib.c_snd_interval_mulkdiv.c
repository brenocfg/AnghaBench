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
struct snd_interval {scalar_t__ min; scalar_t__ max; int openmin; int openmax; scalar_t__ integer; scalar_t__ empty; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 void* muldiv32 (scalar_t__,unsigned int,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  snd_interval_none (struct snd_interval*) ; 

void snd_interval_mulkdiv(const struct snd_interval *a, unsigned int k,
		      const struct snd_interval *b, struct snd_interval *c)
{
	unsigned int r;
	if (a->empty || b->empty) {
		snd_interval_none(c);
		return;
	}
	c->empty = 0;
	c->min = muldiv32(a->min, k, b->max, &r);
	c->openmin = (r || a->openmin || b->openmax);
	if (b->min > 0) {
		c->max = muldiv32(a->max, k, b->min, &r);
		if (r) {
			c->max++;
			c->openmax = 1;
		} else
			c->openmax = (a->openmax || b->openmin);
	} else {
		c->max = UINT_MAX;
		c->openmax = 0;
	}
	c->integer = 0;
}