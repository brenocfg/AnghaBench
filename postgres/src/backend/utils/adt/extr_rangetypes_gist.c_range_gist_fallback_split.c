#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_8__ {void* spl_rdatum; void* spl_ldatum; scalar_t__ spl_nright; scalar_t__ spl_nleft; } ;
struct TYPE_7__ {int n; TYPE_1__* vector; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  int OffsetNumber ;
typedef  TYPE_2__ GistEntryVector ;
typedef  TYPE_3__ GIST_SPLITVEC ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
 int FirstOffsetNumber ; 
 int /*<<< orphan*/  PLACE_LEFT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PLACE_RIGHT (int /*<<< orphan*/ *,int) ; 
 void* RangeTypePGetDatum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
range_gist_fallback_split(TypeCacheEntry *typcache,
						  GistEntryVector *entryvec,
						  GIST_SPLITVEC *v)
{
	RangeType  *left_range = NULL;
	RangeType  *right_range = NULL;
	OffsetNumber i,
				maxoff,
				split_idx;

	maxoff = entryvec->n - 1;
	/* Split entries before this to left page, after to right: */
	split_idx = (maxoff - FirstOffsetNumber) / 2 + FirstOffsetNumber;

	v->spl_nleft = 0;
	v->spl_nright = 0;
	for (i = FirstOffsetNumber; i <= maxoff; i++)
	{
		RangeType  *range = DatumGetRangeTypeP(entryvec->vector[i].key);

		if (i < split_idx)
			PLACE_LEFT(range, i);
		else
			PLACE_RIGHT(range, i);
	}

	v->spl_ldatum = RangeTypePGetDatum(left_range);
	v->spl_rdatum = RangeTypePGetDatum(right_range);
}