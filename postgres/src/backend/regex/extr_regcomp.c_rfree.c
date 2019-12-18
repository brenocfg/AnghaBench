#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vars {int dummy; } ;
struct guts {int /*<<< orphan*/  search; int /*<<< orphan*/  nlacons; int /*<<< orphan*/ * lacons; int /*<<< orphan*/ * tree; int /*<<< orphan*/  cmap; scalar_t__ magic; } ;
struct TYPE_3__ {scalar_t__ re_magic; int /*<<< orphan*/ * re_fns; int /*<<< orphan*/ * re_guts; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct guts*) ; 
 int /*<<< orphan*/  NULLCNFA (int /*<<< orphan*/ ) ; 
 scalar_t__ REMAGIC ; 
 int /*<<< orphan*/  freecm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freecnfa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freelacons (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freesubre (struct vars*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rfree(regex_t *re)
{
	struct guts *g;

	if (re == NULL || re->re_magic != REMAGIC)
		return;

	re->re_magic = 0;			/* invalidate RE */
	g = (struct guts *) re->re_guts;
	re->re_guts = NULL;
	re->re_fns = NULL;
	if (g != NULL)
	{
		g->magic = 0;
		freecm(&g->cmap);
		if (g->tree != NULL)
			freesubre((struct vars *) NULL, g->tree);
		if (g->lacons != NULL)
			freelacons(g->lacons, g->nlacons);
		if (!NULLCNFA(g->search))
			freecnfa(&g->search);
		FREE(g);
	}
}