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
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int AttrNumberIsForUserDefinedAttr (int) ; 
 int MaxAttrNumber ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int bms_num_members (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

AttrNumber *
build_attnums_array(Bitmapset *attrs, int *numattrs)
{
	int			i,
				j;
	AttrNumber *attnums;
	int			num = bms_num_members(attrs);

	if (numattrs)
		*numattrs = num;

	/* build attnums from the bitmapset */
	attnums = (AttrNumber *) palloc(sizeof(AttrNumber) * num);
	i = 0;
	j = -1;
	while ((j = bms_next_member(attrs, j)) >= 0)
	{
		/*
		 * Make sure the bitmap contains only user-defined attributes. As
		 * bitmaps can't contain negative values, this can be violated in two
		 * ways. Firstly, the bitmap might contain 0 as a member, and secondly
		 * the integer value might be larger than MaxAttrNumber.
		 */
		Assert(AttrNumberIsForUserDefinedAttr(j));
		Assert(j <= MaxAttrNumber);

		attnums[i++] = (AttrNumber) j;

		/* protect against overflows */
		Assert(i <= num);
	}

	return attnums;
}