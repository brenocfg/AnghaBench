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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_2__ {scalar_t__ pd_checksum; int /*<<< orphan*/  pd_lsn; } ;
typedef  TYPE_1__* PageHeader ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 scalar_t__ MASK_MARKER ; 
 int /*<<< orphan*/  PageXLogRecPtrSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mask_page_lsn_and_checksum(Page page)
{
	PageHeader	phdr = (PageHeader) page;

	PageXLogRecPtrSet(phdr->pd_lsn, (uint64) MASK_MARKER);
	phdr->pd_checksum = MASK_MARKER;
}