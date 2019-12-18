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
typedef  int int32 ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ BPCHAROID ; 
 int get_typlen (scalar_t__) ; 
 int type_maximum_size (scalar_t__,int) ; 

int32
get_typavgwidth(Oid typid, int32 typmod)
{
	int			typlen = get_typlen(typid);
	int32		maxwidth;

	/*
	 * Easy if it's a fixed-width type
	 */
	if (typlen > 0)
		return typlen;

	/*
	 * type_maximum_size knows the encoding of typmod for some datatypes;
	 * don't duplicate that knowledge here.
	 */
	maxwidth = type_maximum_size(typid, typmod);
	if (maxwidth > 0)
	{
		/*
		 * For BPCHAR, the max width is also the only width.  Otherwise we
		 * need to guess about the typical data width given the max. A sliding
		 * scale for percentage of max width seems reasonable.
		 */
		if (typid == BPCHAROID)
			return maxwidth;
		if (maxwidth <= 32)
			return maxwidth;	/* assume full width */
		if (maxwidth < 1000)
			return 32 + (maxwidth - 32) / 2;	/* assume 50% */

		/*
		 * Beyond 1000, assume we're looking at something like
		 * "varchar(10000)" where the limit isn't actually reached often, and
		 * use a fixed estimate.
		 */
		return 32 + (1000 - 32) / 2;
	}

	/*
	 * Oops, we have no idea ... wild guess time.
	 */
	return 32;
}