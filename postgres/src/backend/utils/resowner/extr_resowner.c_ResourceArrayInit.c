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
struct TYPE_3__ {scalar_t__ capacity; scalar_t__ nitems; scalar_t__ maxitems; int /*<<< orphan*/  invalidval; int /*<<< orphan*/ * itemsarr; } ;
typedef  TYPE_1__ ResourceArray ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static void
ResourceArrayInit(ResourceArray *resarr, Datum invalidval)
{
	/* Assert it's empty */
	Assert(resarr->itemsarr == NULL);
	Assert(resarr->capacity == 0);
	Assert(resarr->nitems == 0);
	Assert(resarr->maxitems == 0);
	/* Remember the appropriate "invalid" value */
	resarr->invalidval = invalidval;
	/* We don't allocate any storage until needed */
}