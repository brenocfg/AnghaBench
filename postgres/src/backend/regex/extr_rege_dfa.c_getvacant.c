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
struct vars {int dummy; } ;
struct arcp {size_t co; struct sset* ss; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct sset {int flags; int /*<<< orphan*/ * lastseen; struct arcp* inchain; struct sset** outs; struct arcp ins; } ;
struct dfa {int ncolors; int /*<<< orphan*/ * lastnopr; int /*<<< orphan*/ * lastpost; struct sset* ssets; } ;
typedef  size_t color ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  FDEBUG (char*) ; 
 int LOCKED ; 
 int NOPROGRESS ; 
 int POSTSTATE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct sset* pickss (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sset *
getvacant(struct vars *v,
		  struct dfa *d,
		  chr *cp,
		  chr *start)
{
	int			i;
	struct sset *ss;
	struct sset *p;
	struct arcp ap;
	color		co;

	ss = pickss(v, d, cp, start);
	if (ss == NULL)
		return NULL;
	assert(!(ss->flags & LOCKED));

	/* clear out its inarcs, including self-referential ones */
	ap = ss->ins;
	while ((p = ap.ss) != NULL)
	{
		co = ap.co;
		FDEBUG(("zapping c%d's %ld outarc\n", (int) (p - d->ssets), (long) co));
		p->outs[co] = NULL;
		ap = p->inchain[co];
		p->inchain[co].ss = NULL;	/* paranoia */
	}
	ss->ins.ss = NULL;

	/* take it off the inarc chains of the ssets reached by its outarcs */
	for (i = 0; i < d->ncolors; i++)
	{
		p = ss->outs[i];
		assert(p != ss);		/* not self-referential */
		if (p == NULL)
			continue;			/* NOTE CONTINUE */
		FDEBUG(("del outarc %d from c%d's in chn\n", i, (int) (p - d->ssets)));
		if (p->ins.ss == ss && p->ins.co == i)
			p->ins = ss->inchain[i];
		else
		{
			struct arcp lastap = {NULL, 0};

			assert(p->ins.ss != NULL);
			for (ap = p->ins; ap.ss != NULL &&
				 !(ap.ss == ss && ap.co == i);
				 ap = ap.ss->inchain[ap.co])
				lastap = ap;
			assert(ap.ss != NULL);
			lastap.ss->inchain[lastap.co] = ss->inchain[i];
		}
		ss->outs[i] = NULL;
		ss->inchain[i].ss = NULL;
	}

	/* if ss was a success state, may need to remember location */
	if ((ss->flags & POSTSTATE) && ss->lastseen != d->lastpost &&
		(d->lastpost == NULL || d->lastpost < ss->lastseen))
		d->lastpost = ss->lastseen;

	/* likewise for a no-progress state */
	if ((ss->flags & NOPROGRESS) && ss->lastseen != d->lastnopr &&
		(d->lastnopr == NULL || d->lastnopr < ss->lastseen))
		d->lastnopr = ss->lastseen;

	return ss;
}