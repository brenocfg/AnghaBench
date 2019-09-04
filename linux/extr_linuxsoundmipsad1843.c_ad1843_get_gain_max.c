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
struct ad1843_gain {int /*<<< orphan*/  lmute; TYPE_1__* lfield; } ;
struct TYPE_2__ {int nbits; } ;

/* Variables and functions */
 struct ad1843_gain** ad1843_gain ; 

int ad1843_get_gain_max(struct snd_ad1843 *ad1843, int id)
{
	const struct ad1843_gain *gp = ad1843_gain[id];
	int ret;

	ret = (1 << gp->lfield->nbits);
	if (!gp->lmute)
		ret -= 1;
	return ret;
}