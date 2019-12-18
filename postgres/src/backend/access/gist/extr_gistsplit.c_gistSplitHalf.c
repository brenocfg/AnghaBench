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
struct TYPE_3__ {int* spl_left; int* spl_right; scalar_t__ spl_nleft; scalar_t__ spl_nright; } ;
typedef  int OffsetNumber ;
typedef  TYPE_1__ GIST_SPLITVEC ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
gistSplitHalf(GIST_SPLITVEC *v, int len)
{
	int			i;

	v->spl_nright = v->spl_nleft = 0;
	v->spl_left = (OffsetNumber *) palloc(len * sizeof(OffsetNumber));
	v->spl_right = (OffsetNumber *) palloc(len * sizeof(OffsetNumber));
	for (i = 1; i <= len; i++)
		if (i < len / 2)
			v->spl_right[v->spl_nright++] = i;
		else
			v->spl_left[v->spl_nleft++] = i;

	/* we need not compute union keys, caller took care of it */
}