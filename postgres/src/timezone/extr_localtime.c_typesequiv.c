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
struct ttinfo {scalar_t__ tt_utoff; scalar_t__ tt_isdst; scalar_t__ tt_ttisstd; scalar_t__ tt_ttisut; size_t tt_desigidx; } ;
struct state {int typecnt; int /*<<< orphan*/ * chars; struct ttinfo* ttis; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
typesequiv(const struct state *sp, int a, int b)
{
	bool		result;

	if (sp == NULL ||
		a < 0 || a >= sp->typecnt ||
		b < 0 || b >= sp->typecnt)
		result = false;
	else
	{
		const struct ttinfo *ap = &sp->ttis[a];
		const struct ttinfo *bp = &sp->ttis[b];

		result = (ap->tt_utoff == bp->tt_utoff
				  && ap->tt_isdst == bp->tt_isdst
				  && ap->tt_ttisstd == bp->tt_ttisstd
				  && ap->tt_ttisut == bp->tt_ttisut
				  && (strcmp(&sp->chars[ap->tt_desigidx],
							 &sp->chars[bp->tt_desigidx])
					  == 0));
	}
	return result;
}