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
struct colormap {TYPE_1__* cd; } ;
struct cnfa {int pre; scalar_t__* bos; scalar_t__* eos; scalar_t__ ncolors; int post; struct carc** states; } ;
struct carc {scalar_t__ co; int to; } ;
typedef  scalar_t__ color ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_2__ {int nschrs; scalar_t__ nuchrs; int /*<<< orphan*/  firstchr; } ;

/* Variables and functions */
 scalar_t__ COLORLESS ; 
 scalar_t__ GETCOLOR (struct colormap*,int /*<<< orphan*/ ) ; 
 int REG_EXACT ; 
 int REG_NOMATCH ; 
 int REG_PREFIX ; 

__attribute__((used)) static int						/* regprefix return code */
findprefix(struct cnfa *cnfa,
		   struct colormap *cm,
		   chr *string,
		   size_t *slength)
{
	int			st;
	int			nextst;
	color		thiscolor;
	chr			c;
	struct carc *ca;

	/*
	 * The "pre" state must have only BOS/BOL outarcs, else pattern isn't
	 * anchored left.  If we have both BOS and BOL, they must go to the same
	 * next state.
	 */
	st = cnfa->pre;
	nextst = -1;
	for (ca = cnfa->states[st]; ca->co != COLORLESS; ca++)
	{
		if (ca->co == cnfa->bos[0] || ca->co == cnfa->bos[1])
		{
			if (nextst == -1)
				nextst = ca->to;
			else if (nextst != ca->to)
				return REG_NOMATCH;
		}
		else
			return REG_NOMATCH;
	}
	if (nextst == -1)
		return REG_NOMATCH;

	/*
	 * Scan through successive states, stopping as soon as we find one with
	 * more than one acceptable transition character (either multiple colors
	 * on out-arcs, or a color with more than one member chr).
	 *
	 * We could find a state with multiple out-arcs that are all labeled with
	 * the same singleton color; this comes from patterns like "^ab(cde|cxy)".
	 * In that case we add the chr "c" to the output string but then exit the
	 * loop with nextst == -1.  This leaves a little bit on the table: if the
	 * pattern is like "^ab(cde|cdy)", we won't notice that "d" could be added
	 * to the prefix.  But chasing multiple parallel state chains doesn't seem
	 * worth the trouble.
	 */
	do
	{
		st = nextst;
		nextst = -1;
		thiscolor = COLORLESS;
		for (ca = cnfa->states[st]; ca->co != COLORLESS; ca++)
		{
			/* We can ignore BOS/BOL arcs */
			if (ca->co == cnfa->bos[0] || ca->co == cnfa->bos[1])
				continue;
			/* ... but EOS/EOL arcs terminate the search, as do LACONs */
			if (ca->co == cnfa->eos[0] || ca->co == cnfa->eos[1] ||
				ca->co >= cnfa->ncolors)
			{
				thiscolor = COLORLESS;
				break;
			}
			if (thiscolor == COLORLESS)
			{
				/* First plain outarc */
				thiscolor = ca->co;
				nextst = ca->to;
			}
			else if (thiscolor == ca->co)
			{
				/* Another plain outarc for same color */
				nextst = -1;
			}
			else
			{
				/* More than one plain outarc color terminates the search */
				thiscolor = COLORLESS;
				break;
			}
		}
		/* Done if we didn't find exactly one color on plain outarcs */
		if (thiscolor == COLORLESS)
			break;
		/* The color must be a singleton */
		if (cm->cd[thiscolor].nschrs != 1)
			break;
		/* Must not have any high-color-map entries */
		if (cm->cd[thiscolor].nuchrs != 0)
			break;

		/*
		 * Identify the color's sole member chr and add it to the prefix
		 * string.  In general the colormap data structure doesn't provide a
		 * way to find color member chrs, except by trying GETCOLOR() on each
		 * possible chr value, which won't do at all.  However, for the cases
		 * we care about it should be sufficient to test the "firstchr" value,
		 * that is the first chr ever added to the color.  There are cases
		 * where this might no longer be a member of the color (so we do need
		 * to test), but none of them are likely to arise for a character that
		 * is a member of a common prefix.  If we do hit such a corner case,
		 * we just fall out without adding anything to the prefix string.
		 */
		c = cm->cd[thiscolor].firstchr;
		if (GETCOLOR(cm, c) != thiscolor)
			break;

		string[(*slength)++] = c;

		/* Advance to next state, but only if we have a unique next state */
	} while (nextst != -1);

	/*
	 * If we ended at a state that only has EOS/EOL outarcs leading to the
	 * "post" state, then we have an exact-match string.  Note this is true
	 * even if the string is of zero length.
	 */
	nextst = -1;
	for (ca = cnfa->states[st]; ca->co != COLORLESS; ca++)
	{
		if (ca->co == cnfa->eos[0] || ca->co == cnfa->eos[1])
		{
			if (nextst == -1)
				nextst = ca->to;
			else if (nextst != ca->to)
			{
				nextst = -1;
				break;
			}
		}
		else
		{
			nextst = -1;
			break;
		}
	}
	if (nextst == cnfa->post)
		return REG_EXACT;

	/*
	 * Otherwise, if we were unable to identify any prefix characters, say
	 * NOMATCH --- the pattern is anchored left, but doesn't specify any
	 * particular first character.
	 */
	if (*slength > 0)
		return REG_PREFIX;

	return REG_NOMATCH;
}