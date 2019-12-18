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
struct colormap {struct colordesc* cd; } ;
struct colordesc {int nuchrs; int /*<<< orphan*/  flags; int /*<<< orphan*/  firstchr; int /*<<< orphan*/ * arcs; int /*<<< orphan*/  sub; scalar_t__ nschrs; } ;
typedef  size_t color ;

/* Variables and functions */
 int /*<<< orphan*/  CHR_MIN ; 
 scalar_t__ CISERR () ; 
 size_t COLORLESS ; 
 int /*<<< orphan*/  NOSUB ; 
 int /*<<< orphan*/  PSEUDO ; 
 size_t newcolor (struct colormap*) ; 

__attribute__((used)) static color
pseudocolor(struct colormap *cm)
{
	color		co;
	struct colordesc *cd;

	co = newcolor(cm);
	if (CISERR())
		return COLORLESS;
	cd = &cm->cd[co];
	cd->nschrs = 0;
	cd->nuchrs = 1;				/* pretend it is in the upper map */
	cd->sub = NOSUB;
	cd->arcs = NULL;
	cd->firstchr = CHR_MIN;
	cd->flags = PSEUDO;
	return co;
}