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
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_2__ {int /*<<< orphan*/  pd_upper; int /*<<< orphan*/  pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;

/* Variables and functions */
 scalar_t__ BLCKSZ ; 
 int /*<<< orphan*/  MASK_MARKER ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
mask_page_content(Page page)
{
	/* Mask Page Content */
	memset(page + SizeOfPageHeaderData, MASK_MARKER,
		   BLCKSZ - SizeOfPageHeaderData);

	/* Mask pd_lower and pd_upper */
	memset(&((PageHeader) page)->pd_lower, MASK_MARKER,
		   sizeof(uint16));
	memset(&((PageHeader) page)->pd_upper, MASK_MARKER,
		   sizeof(uint16));
}