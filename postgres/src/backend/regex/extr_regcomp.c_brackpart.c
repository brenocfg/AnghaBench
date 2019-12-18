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
struct vars {int nexttype; scalar_t__ nextvalue; scalar_t__* now; int cflags; } ;
struct state {int dummy; } ;
struct cvec {int dummy; } ;
typedef  scalar_t__ chr ;

/* Variables and functions */
#define  CCLASS 132 
#define  COLLEL 131 
#define  ECLASS 130 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  NOERR () ; 
 int /*<<< orphan*/  NOTE (int /*<<< orphan*/ ) ; 
#define  PLAIN 129 
#define  RANGE 128 
 int /*<<< orphan*/  REG_ASSERT ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  REG_UUNPORT ; 
 scalar_t__ SEE (int const) ; 
 struct cvec* cclass (struct vars*,scalar_t__ const*,scalar_t__ const*,int) ; 
 struct cvec* eclass (struct vars*,scalar_t__,int) ; 
 scalar_t__ element (struct vars*,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  onechr (struct vars*,scalar_t__,struct state*,struct state*) ; 
 struct cvec* range (struct vars*,scalar_t__,scalar_t__,int) ; 
 scalar_t__* scanplain (struct vars*) ; 
 int /*<<< orphan*/  subcolorcvec (struct vars*,struct cvec*,struct state*,struct state*) ; 

__attribute__((used)) static void
brackpart(struct vars *v,
		  struct state *lp,
		  struct state *rp)
{
	chr			startc;
	chr			endc;
	struct cvec *cv;
	const chr  *startp;
	const chr  *endp;
	chr			c[1];

	/* parse something, get rid of special cases, take shortcuts */
	switch (v->nexttype)
	{
		case RANGE:				/* a-b-c or other botch */
			ERR(REG_ERANGE);
			return;
			break;
		case PLAIN:
			c[0] = v->nextvalue;
			NEXT();
			/* shortcut for ordinary chr (not range) */
			if (!SEE(RANGE))
			{
				onechr(v, c[0], lp, rp);
				return;
			}
			startc = element(v, c, c + 1);
			NOERR();
			break;
		case COLLEL:
			startp = v->now;
			endp = scanplain(v);
			INSIST(startp < endp, REG_ECOLLATE);
			NOERR();
			startc = element(v, startp, endp);
			NOERR();
			break;
		case ECLASS:
			startp = v->now;
			endp = scanplain(v);
			INSIST(startp < endp, REG_ECOLLATE);
			NOERR();
			startc = element(v, startp, endp);
			NOERR();
			cv = eclass(v, startc, (v->cflags & REG_ICASE));
			NOERR();
			subcolorcvec(v, cv, lp, rp);
			return;
			break;
		case CCLASS:
			startp = v->now;
			endp = scanplain(v);
			INSIST(startp < endp, REG_ECTYPE);
			NOERR();
			cv = cclass(v, startp, endp, (v->cflags & REG_ICASE));
			NOERR();
			subcolorcvec(v, cv, lp, rp);
			return;
			break;
		default:
			ERR(REG_ASSERT);
			return;
			break;
	}

	if (SEE(RANGE))
	{
		NEXT();
		switch (v->nexttype)
		{
			case PLAIN:
			case RANGE:
				c[0] = v->nextvalue;
				NEXT();
				endc = element(v, c, c + 1);
				NOERR();
				break;
			case COLLEL:
				startp = v->now;
				endp = scanplain(v);
				INSIST(startp < endp, REG_ECOLLATE);
				NOERR();
				endc = element(v, startp, endp);
				NOERR();
				break;
			default:
				ERR(REG_ERANGE);
				return;
				break;
		}
	}
	else
		endc = startc;

	/*
	 * Ranges are unportable.  Actually, standard C does guarantee that digits
	 * are contiguous, but making that an exception is just too complicated.
	 */
	if (startc != endc)
		NOTE(REG_UUNPORT);
	cv = range(v, startc, endc, (v->cflags & REG_ICASE));
	NOERR();
	subcolorcvec(v, cv, lp, rp);
}