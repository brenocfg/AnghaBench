#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_5__ {scalar_t__ n_errors; } ;
struct TYPE_6__ {TYPE_1__ public; int /*<<< orphan*/ * connection; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int restore_toc_entry (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

int
parallel_restore(ArchiveHandle *AH, TocEntry *te)
{
	int			status;

	Assert(AH->connection != NULL);

	/* Count only errors associated with this TOC entry */
	AH->public.n_errors = 0;

	/* Restore the TOC item */
	status = restore_toc_entry(AH, te, true);

	return status;
}