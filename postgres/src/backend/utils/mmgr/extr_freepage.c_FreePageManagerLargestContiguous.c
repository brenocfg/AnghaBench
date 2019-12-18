#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * freelist; } ;
struct TYPE_6__ {scalar_t__ npages; int /*<<< orphan*/  next; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ FreePageSpanLeader ;
typedef  TYPE_2__ FreePageManager ;

/* Variables and functions */
 int FPM_NUM_FREELISTS ; 
 char* fpm_segment_base (TYPE_2__*) ; 
 TYPE_1__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Size
FreePageManagerLargestContiguous(FreePageManager *fpm)
{
	char	   *base;
	Size		largest;

	base = fpm_segment_base(fpm);
	largest = 0;
	if (!relptr_is_null(fpm->freelist[FPM_NUM_FREELISTS - 1]))
	{
		FreePageSpanLeader *candidate;

		candidate = relptr_access(base, fpm->freelist[FPM_NUM_FREELISTS - 1]);
		do
		{
			if (candidate->npages > largest)
				largest = candidate->npages;
			candidate = relptr_access(base, candidate->next);
		} while (candidate != NULL);
	}
	else
	{
		Size		f = FPM_NUM_FREELISTS - 1;

		do
		{
			--f;
			if (!relptr_is_null(fpm->freelist[f]))
			{
				largest = f + 1;
				break;
			}
		} while (f > 0);
	}

	return largest;
}