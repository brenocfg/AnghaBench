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
struct nfa {int dummy; } ;
struct colormap {struct colordesc* cd; } ;
struct colordesc {size_t sub; scalar_t__ nschrs; scalar_t__ nuchrs; struct arc* arcs; } ;
struct arc {size_t co; int /*<<< orphan*/  to; int /*<<< orphan*/  from; int /*<<< orphan*/  type; struct arc* colorchain; } ;
typedef  size_t color ;

/* Variables and functions */
 struct colordesc* CDEND (struct colormap*) ; 
 size_t NOSUB ; 
 scalar_t__ UNUSEDCOLOR (struct colordesc*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  colorchain (struct colormap*,struct arc*) ; 
 int /*<<< orphan*/  freecolor (struct colormap*,size_t) ; 
 int /*<<< orphan*/  newarc (struct nfa*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uncolorchain (struct colormap*,struct arc*) ; 

__attribute__((used)) static void
okcolors(struct nfa *nfa,
		 struct colormap *cm)
{
	struct colordesc *cd;
	struct colordesc *end = CDEND(cm);
	struct colordesc *scd;
	struct arc *a;
	color		co;
	color		sco;

	for (cd = cm->cd, co = 0; cd < end; cd++, co++)
	{
		sco = cd->sub;
		if (UNUSEDCOLOR(cd) || sco == NOSUB)
		{
			/* has no subcolor, no further action */
		}
		else if (sco == co)
		{
			/* is subcolor, let parent deal with it */
		}
		else if (cd->nschrs == 0 && cd->nuchrs == 0)
		{
			/* parent empty, its arcs change color to subcolor */
			cd->sub = NOSUB;
			scd = &cm->cd[sco];
			assert(scd->nschrs > 0 || scd->nuchrs > 0);
			assert(scd->sub == sco);
			scd->sub = NOSUB;
			while ((a = cd->arcs) != NULL)
			{
				assert(a->co == co);
				uncolorchain(cm, a);
				a->co = sco;
				colorchain(cm, a);
			}
			freecolor(cm, co);
		}
		else
		{
			/* parent's arcs must gain parallel subcolor arcs */
			cd->sub = NOSUB;
			scd = &cm->cd[sco];
			assert(scd->nschrs > 0 || scd->nuchrs > 0);
			assert(scd->sub == sco);
			scd->sub = NOSUB;
			for (a = cd->arcs; a != NULL; a = a->colorchain)
			{
				assert(a->co == co);
				newarc(nfa, a->type, sco, a->from, a->to);
			}
		}
	}
}