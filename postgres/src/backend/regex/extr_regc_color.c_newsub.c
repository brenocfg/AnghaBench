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
typedef  size_t color ;
struct TYPE_2__ {size_t sub; int nschrs; int nuchrs; } ;

/* Variables and functions */
 int CISERR () ; 
 size_t COLORLESS ; 
 size_t NOSUB ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t newcolor (struct colormap*) ; 

__attribute__((used)) static color
newsub(struct colormap *cm,
	   color co)
{
	color		sco;			/* new subcolor */

	sco = cm->cd[co].sub;
	if (sco == NOSUB)
	{							/* color has no open subcolor */
		/* optimization: singly-referenced color need not be subcolored */
		if ((cm->cd[co].nschrs + cm->cd[co].nuchrs) == 1)
			return co;
		sco = newcolor(cm);		/* must create subcolor */
		if (sco == COLORLESS)
		{
			assert(CISERR());
			return COLORLESS;
		}
		cm->cd[co].sub = sco;
		cm->cd[sco].sub = sco;	/* open subcolor points to self */
	}
	assert(sco != NOSUB);

	return sco;
}