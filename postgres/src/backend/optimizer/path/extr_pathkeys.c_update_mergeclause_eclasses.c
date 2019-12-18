#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mergeopfamilies; TYPE_1__* right_ec; TYPE_2__* left_ec; } ;
struct TYPE_6__ {struct TYPE_6__* ec_merged; } ;
struct TYPE_5__ {struct TYPE_5__* ec_merged; } ;
typedef  TYPE_3__ RestrictInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ NIL ; 

void
update_mergeclause_eclasses(PlannerInfo *root, RestrictInfo *restrictinfo)
{
	/* Should be a merge clause ... */
	Assert(restrictinfo->mergeopfamilies != NIL);
	/* ... with pointers already set */
	Assert(restrictinfo->left_ec != NULL);
	Assert(restrictinfo->right_ec != NULL);

	/* Chase up to the top as needed */
	while (restrictinfo->left_ec->ec_merged)
		restrictinfo->left_ec = restrictinfo->left_ec->ec_merged;
	while (restrictinfo->right_ec->ec_merged)
		restrictinfo->right_ec = restrictinfo->right_ec->ec_merged;
}