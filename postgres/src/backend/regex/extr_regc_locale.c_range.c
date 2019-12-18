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
struct vars {int /*<<< orphan*/  re; } ;
struct cvec {scalar_t__ nchrs; scalar_t__ chrspace; } ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOERRN () ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 int /*<<< orphan*/  addchr (struct cvec*,scalar_t__) ; 
 int /*<<< orphan*/  addrange (struct cvec*,scalar_t__,scalar_t__) ; 
 scalar_t__ before (scalar_t__,scalar_t__) ; 
 struct cvec* getcvec (struct vars*,int,int) ; 
 scalar_t__ pg_wc_tolower (scalar_t__) ; 
 scalar_t__ pg_wc_toupper (scalar_t__) ; 

__attribute__((used)) static struct cvec *
range(struct vars *v,			/* context */
	  chr a,					/* range start */
	  chr b,					/* range end, might equal a */
	  int cases)				/* case-independent? */
{
	int			nchrs;
	struct cvec *cv;
	chr			c,
				cc;

	if (a != b && !before(a, b))
	{
		ERR(REG_ERANGE);
		return NULL;
	}

	if (!cases)
	{							/* easy version */
		cv = getcvec(v, 0, 1);
		NOERRN();
		addrange(cv, a, b);
		return cv;
	}

	/*
	 * When case-independent, it's hard to decide when cvec ranges are usable,
	 * so for now at least, we won't try.  We use a range for the originally
	 * specified chrs and then add on any case-equivalents that are outside
	 * that range as individual chrs.
	 *
	 * To ensure sane behavior if someone specifies a very large range, limit
	 * the allocation size to 100000 chrs (arbitrary) and check for overrun
	 * inside the loop below.
	 */
	nchrs = b - a + 1;
	if (nchrs <= 0 || nchrs > 100000)
		nchrs = 100000;

	cv = getcvec(v, nchrs, 1);
	NOERRN();
	addrange(cv, a, b);

	for (c = a; c <= b; c++)
	{
		cc = pg_wc_tolower(c);
		if (cc != c &&
			(before(cc, a) || before(b, cc)))
		{
			if (cv->nchrs >= cv->chrspace)
			{
				ERR(REG_ETOOBIG);
				return NULL;
			}
			addchr(cv, cc);
		}
		cc = pg_wc_toupper(c);
		if (cc != c &&
			(before(cc, a) || before(b, cc)))
		{
			if (cv->nchrs >= cv->chrspace)
			{
				ERR(REG_ETOOBIG);
				return NULL;
			}
			addchr(cv, cc);
		}
		if (CANCEL_REQUESTED(v->re))
		{
			ERR(REG_CANCEL);
			return NULL;
		}
	}

	return cv;
}