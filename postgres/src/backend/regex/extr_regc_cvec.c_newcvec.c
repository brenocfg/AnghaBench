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
struct cvec {int chrspace; int rangespace; int /*<<< orphan*/ * chrs; int /*<<< orphan*/ * ranges; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 scalar_t__ MALLOC (size_t) ; 
 struct cvec* clearcvec (struct cvec*) ; 

__attribute__((used)) static struct cvec *
newcvec(int nchrs,				/* to hold this many chrs... */
		int nranges)			/* ... and this many ranges */
{
	size_t		nc = (size_t) nchrs + (size_t) nranges * 2;
	size_t		n = sizeof(struct cvec) + nc * sizeof(chr);
	struct cvec *cv = (struct cvec *) MALLOC(n);

	if (cv == NULL)
		return NULL;
	cv->chrspace = nchrs;
	cv->chrs = (chr *) (((char *) cv) + sizeof(struct cvec));
	cv->ranges = cv->chrs + nchrs;
	cv->rangespace = nranges;
	return clearcvec(cv);
}