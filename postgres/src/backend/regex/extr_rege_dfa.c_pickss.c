#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vars {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  co; int /*<<< orphan*/ * ss; } ;
struct sset {int flags; int /*<<< orphan*/ * lastseen; TYPE_2__* inchain; int /*<<< orphan*/ ** outs; TYPE_1__ ins; int /*<<< orphan*/ * states; } ;
struct dfa {int nssused; int nssets; int wordsper; int ncolors; struct sset* ssets; struct sset* search; TYPE_2__* incarea; int /*<<< orphan*/ ** outsarea; int /*<<< orphan*/ * statesarea; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_4__ {int /*<<< orphan*/ * ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDEBUG (char*) ; 
 int LOCKED ; 
 int /*<<< orphan*/  REG_ASSERT ; 
 int /*<<< orphan*/  WHITE ; 

__attribute__((used)) static struct sset *
pickss(struct vars *v,
	   struct dfa *d,
	   chr *cp,
	   chr *start)
{
	int			i;
	struct sset *ss;
	struct sset *end;
	chr		   *ancient;

	/* shortcut for cases where cache isn't full */
	if (d->nssused < d->nssets)
	{
		i = d->nssused;
		d->nssused++;
		ss = &d->ssets[i];
		FDEBUG(("new c%d\n", i));
		/* set up innards */
		ss->states = &d->statesarea[i * d->wordsper];
		ss->flags = 0;
		ss->ins.ss = NULL;
		ss->ins.co = WHITE;		/* give it some value */
		ss->outs = &d->outsarea[i * d->ncolors];
		ss->inchain = &d->incarea[i * d->ncolors];
		for (i = 0; i < d->ncolors; i++)
		{
			ss->outs[i] = NULL;
			ss->inchain[i].ss = NULL;
		}
		return ss;
	}

	/* look for oldest, or old enough anyway */
	if (cp - start > d->nssets * 2 / 3) /* oldest 33% are expendable */
		ancient = cp - d->nssets * 2 / 3;
	else
		ancient = start;
	for (ss = d->search, end = &d->ssets[d->nssets]; ss < end; ss++)
		if ((ss->lastseen == NULL || ss->lastseen < ancient) &&
			!(ss->flags & LOCKED))
		{
			d->search = ss + 1;
			FDEBUG(("replacing c%d\n", (int) (ss - d->ssets)));
			return ss;
		}
	for (ss = d->ssets, end = d->search; ss < end; ss++)
		if ((ss->lastseen == NULL || ss->lastseen < ancient) &&
			!(ss->flags & LOCKED))
		{
			d->search = ss + 1;
			FDEBUG(("replacing c%d\n", (int) (ss - d->ssets)));
			return ss;
		}

	/* nobody's old enough?!? -- something's really wrong */
	FDEBUG(("cannot find victim to replace!\n"));
	ERR(REG_ASSERT);
	return NULL;
}