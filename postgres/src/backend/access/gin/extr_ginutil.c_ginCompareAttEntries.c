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
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int ginCompareEntries (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ginCompareAttEntries(GinState *ginstate,
					 OffsetNumber attnuma, Datum a, GinNullCategory categorya,
					 OffsetNumber attnumb, Datum b, GinNullCategory categoryb)
{
	/* attribute number is the first sort key */
	if (attnuma != attnumb)
		return (attnuma < attnumb) ? -1 : 1;

	return ginCompareEntries(ginstate, attnuma, a, categorya, b, categoryb);
}