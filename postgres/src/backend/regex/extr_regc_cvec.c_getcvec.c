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
struct vars {struct cvec* cv; } ;
struct cvec {int chrspace; int rangespace; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 struct cvec* clearcvec (struct cvec*) ; 
 int /*<<< orphan*/  freecvec (struct cvec*) ; 
 struct cvec* newcvec (int,int) ; 

__attribute__((used)) static struct cvec *
getcvec(struct vars *v,			/* context */
		int nchrs,				/* to hold this many chrs... */
		int nranges)			/* ... and this many ranges */
{
	/* recycle existing transient cvec if large enough */
	if (v->cv != NULL && nchrs <= v->cv->chrspace &&
		nranges <= v->cv->rangespace)
		return clearcvec(v->cv);

	/* nope, make a new one */
	if (v->cv != NULL)
		freecvec(v->cv);
	v->cv = newcvec(nchrs, nranges);
	if (v->cv == NULL)
		ERR(REG_ESPACE);

	return v->cv;
}