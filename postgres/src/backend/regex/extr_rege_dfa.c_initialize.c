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
struct vars {int dummy; } ;
struct sset {int flags; int /*<<< orphan*/ * lastseen; scalar_t__* states; int /*<<< orphan*/  hash; } ;
struct dfa {int nssused; int wordsper; int /*<<< orphan*/ * lastnopr; int /*<<< orphan*/ * lastpost; struct sset* ssets; TYPE_1__* cnfa; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_2__ {int /*<<< orphan*/  post; int /*<<< orphan*/  pre; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSET (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH (scalar_t__*,int) ; 
 int LOCKED ; 
 int NOPROGRESS ; 
 int STARTER ; 
 int /*<<< orphan*/  assert (int) ; 
 struct sset* getvacant (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sset *
initialize(struct vars *v,
		   struct dfa *d,
		   chr *start)
{
	struct sset *ss;
	int			i;

	/* is previous one still there? */
	if (d->nssused > 0 && (d->ssets[0].flags & STARTER))
		ss = &d->ssets[0];
	else
	{							/* no, must (re)build it */
		ss = getvacant(v, d, start, start);
		if (ss == NULL)
			return NULL;
		for (i = 0; i < d->wordsper; i++)
			ss->states[i] = 0;
		BSET(ss->states, d->cnfa->pre);
		ss->hash = HASH(ss->states, d->wordsper);
		assert(d->cnfa->pre != d->cnfa->post);
		ss->flags = STARTER | LOCKED | NOPROGRESS;
		/* lastseen dealt with below */
	}

	for (i = 0; i < d->nssused; i++)
		d->ssets[i].lastseen = NULL;
	ss->lastseen = start;		/* maybe untrue, but harmless */
	d->lastpost = NULL;
	d->lastnopr = NULL;
	return ss;
}