#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_ad1843 {int dummy; } ;
struct ad1843_gain {int /*<<< orphan*/  rmute; TYPE_1__* lmute; scalar_t__ negative; int /*<<< orphan*/  rfield; TYPE_1__* lfield; } ;
struct TYPE_2__ {int nbits; } ;

/* Variables and functions */
 struct ad1843_gain** ad1843_gain ; 
 int /*<<< orphan*/  ad1843_read_multi (struct snd_ad1843*,int,TYPE_1__*,int*,int /*<<< orphan*/ ,int*) ; 

int ad1843_get_gain(struct snd_ad1843 *ad1843, int id)
{
	int lg, rg, lm, rm;
	const struct ad1843_gain *gp = ad1843_gain[id];
	unsigned short mask = (1 << gp->lfield->nbits) - 1;

	ad1843_read_multi(ad1843, 2, gp->lfield, &lg, gp->rfield, &rg);
	if (gp->negative) {
		lg = mask - lg;
		rg = mask - rg;
	}
	if (gp->lmute) {
		ad1843_read_multi(ad1843, 2, gp->lmute, &lm, gp->rmute, &rm);
		if (lm)
			lg = 0;
		if (rm)
			rg = 0;
	}
	return lg << 0 | rg << 8;
}