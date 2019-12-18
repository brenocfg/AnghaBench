#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ varno; scalar_t__ varattno; scalar_t__ resno; } ;
typedef  TYPE_1__ tlist_vinfo ;
struct TYPE_10__ {int num_vars; TYPE_1__* vars; } ;
typedef  TYPE_2__ indexed_tlist ;
struct TYPE_11__ {scalar_t__ varno; scalar_t__ varattno; scalar_t__ varnoold; } ;
typedef  TYPE_3__ Var ;
typedef  scalar_t__ Index ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 TYPE_3__* copyVar (TYPE_3__*) ; 

__attribute__((used)) static Var *
search_indexed_tlist_for_var(Var *var, indexed_tlist *itlist,
							 Index newvarno, int rtoffset)
{
	Index		varno = var->varno;
	AttrNumber	varattno = var->varattno;
	tlist_vinfo *vinfo;
	int			i;

	vinfo = itlist->vars;
	i = itlist->num_vars;
	while (i-- > 0)
	{
		if (vinfo->varno == varno && vinfo->varattno == varattno)
		{
			/* Found a match */
			Var		   *newvar = copyVar(var);

			newvar->varno = newvarno;
			newvar->varattno = vinfo->resno;
			if (newvar->varnoold > 0)
				newvar->varnoold += rtoffset;
			return newvar;
		}
		vinfo++;
	}
	return NULL;				/* no match */
}