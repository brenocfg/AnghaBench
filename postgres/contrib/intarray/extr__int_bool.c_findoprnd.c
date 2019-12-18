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
typedef  size_t int32 ;
struct TYPE_3__ {scalar_t__ type; size_t val; int left; } ;
typedef  TYPE_1__ ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ OPR ; 
 scalar_t__ VAL ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static void
findoprnd(ITEM *ptr, int32 *pos)
{
	/* since this function recurses, it could be driven to stack overflow. */
	check_stack_depth();

#ifdef BS_DEBUG
	elog(DEBUG3, (ptr[*pos].type == OPR) ?
		 "%d  %c" : "%d  %d", *pos, ptr[*pos].val);
#endif
	if (ptr[*pos].type == VAL)
	{
		ptr[*pos].left = 0;
		(*pos)--;
	}
	else if (ptr[*pos].val == (int32) '!')
	{
		ptr[*pos].left = -1;
		(*pos)--;
		findoprnd(ptr, pos);
	}
	else
	{
		ITEM	   *curitem = &ptr[*pos];
		int32		tmp = *pos;

		(*pos)--;
		findoprnd(ptr, pos);
		curitem->left = *pos - tmp;
		findoprnd(ptr, pos);
	}
}