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
struct TYPE_2__ {int /*<<< orphan*/  pd_checksum; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  DataChecksumsEnabled () ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  pg_checksum_page (char*,int /*<<< orphan*/ ) ; 

void
PageSetChecksumInplace(Page page, BlockNumber blkno)
{
	/* If we don't need a checksum, just return */
	if (PageIsNew(page) || !DataChecksumsEnabled())
		return;

	((PageHeader) page)->pd_checksum = pg_checksum_page((char *) page, blkno);
}