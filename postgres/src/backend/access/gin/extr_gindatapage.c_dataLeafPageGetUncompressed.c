#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int maxoff; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GinDataPageGetData (int /*<<< orphan*/ ) ; 
 TYPE_1__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsCompressed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ItemPointer
dataLeafPageGetUncompressed(Page page, int *nitems)
{
	ItemPointer items;

	Assert(!GinPageIsCompressed(page));

	/*
	 * In the old pre-9.4 page format, the whole page content is used for
	 * uncompressed items, and the number of items is stored in 'maxoff'
	 */
	items = (ItemPointer) GinDataPageGetData(page);
	*nitems = GinPageGetOpaque(page)->maxoff;

	return items;
}