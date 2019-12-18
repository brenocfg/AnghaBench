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
struct colormap {size_t max; scalar_t__ free; struct colordesc* cd; } ;
struct colordesc {size_t sub; scalar_t__ nschrs; scalar_t__ nuchrs; int /*<<< orphan*/  flags; int /*<<< orphan*/ * arcs; } ;
typedef  size_t color ;

/* Variables and functions */
 int /*<<< orphan*/  FREECOL ; 
 size_t NOSUB ; 
 scalar_t__ UNUSEDCOLOR (struct colordesc*) ; 
 size_t WHITE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
freecolor(struct colormap *cm,
		  color co)
{
	struct colordesc *cd = &cm->cd[co];
	color		pco,
				nco;			/* for freelist scan */

	assert(co >= 0);
	if (co == WHITE)
		return;

	assert(cd->arcs == NULL);
	assert(cd->sub == NOSUB);
	assert(cd->nschrs == 0);
	assert(cd->nuchrs == 0);
	cd->flags = FREECOL;

	if ((size_t) co == cm->max)
	{
		while (cm->max > WHITE && UNUSEDCOLOR(&cm->cd[cm->max]))
			cm->max--;
		assert(cm->free >= 0);
		while ((size_t) cm->free > cm->max)
			cm->free = cm->cd[cm->free].sub;
		if (cm->free > 0)
		{
			assert(cm->free < cm->max);
			pco = cm->free;
			nco = cm->cd[pco].sub;
			while (nco > 0)
				if ((size_t) nco > cm->max)
				{
					/* take this one out of freelist */
					nco = cm->cd[nco].sub;
					cm->cd[pco].sub = nco;
				}
				else
				{
					assert(nco < cm->max);
					pco = nco;
					nco = cm->cd[pco].sub;
				}
		}
	}
	else
	{
		cd->sub = cm->free;
		cm->free = (color) (cd - cm->cd);
	}
}