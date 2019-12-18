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
struct vars {int err; } ;
struct cvec {scalar_t__ nchrs; int /*<<< orphan*/ * chrs; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  element (struct vars*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 struct cvec* range (struct vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static chr
chrnamed(struct vars *v,
		 const chr *startp,		/* start of name */
		 const chr *endp,		/* just past end of name */
		 chr lastresort)		/* what to return if name lookup fails */
{
	chr			c;
	int			errsave;
	int			e;
	struct cvec *cv;

	errsave = v->err;
	v->err = 0;
	c = element(v, startp, endp);
	e = v->err;
	v->err = errsave;

	if (e != 0)
		return lastresort;

	cv = range(v, c, c, 0);
	if (cv->nchrs == 0)
		return lastresort;
	return cv->chrs[0];
}