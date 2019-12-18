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
struct TYPE_3__ {int p_rel_visible; int p_cols_visible; int p_lateral_only; int p_lateral_ok; int /*<<< orphan*/ * p_rte; } ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ ParseNamespaceItem ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static ParseNamespaceItem *
makeNamespaceItem(RangeTblEntry *rte, bool rel_visible, bool cols_visible,
				  bool lateral_only, bool lateral_ok)
{
	ParseNamespaceItem *nsitem;

	nsitem = (ParseNamespaceItem *) palloc(sizeof(ParseNamespaceItem));
	nsitem->p_rte = rte;
	nsitem->p_rel_visible = rel_visible;
	nsitem->p_cols_visible = cols_visible;
	nsitem->p_lateral_only = lateral_only;
	nsitem->p_lateral_ok = lateral_ok;
	return nsitem;
}