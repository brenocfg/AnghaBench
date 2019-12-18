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
struct vars {int /*<<< orphan*/ * start; } ;
struct sset {int flags; int /*<<< orphan*/ * lastseen; } ;
struct dfa {int nssused; struct sset* ssets; int /*<<< orphan*/ * lastnopr; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int NOPROGRESS ; 

__attribute__((used)) static chr *					/* endpoint, or NULL */
lastcold(struct vars *v,
		 struct dfa *d)
{
	struct sset *ss;
	chr		   *nopr;
	int			i;

	nopr = d->lastnopr;
	if (nopr == NULL)
		nopr = v->start;
	for (ss = d->ssets, i = d->nssused; i > 0; ss++, i--)
		if ((ss->flags & NOPROGRESS) && nopr < ss->lastseen)
			nopr = ss->lastseen;
	return nopr;
}