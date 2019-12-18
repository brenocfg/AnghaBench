#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_12__ {int /*<<< orphan*/  n_errors; } ;
struct TYPE_14__ {TYPE_1__ public; } ;
typedef  int /*<<< orphan*/  ParallelReadyList ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int WORKER_CREATE_DONE ; 
 int WORKER_IGNORED_ERRORS ; 
 int WORKER_INHIBIT_DATA ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  inhibit_data_for_failed_table (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mark_create_done (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reduce_dependencies (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mark_restore_job_done(ArchiveHandle *AH,
					  TocEntry *te,
					  int status,
					  void *callback_data)
{
	ParallelReadyList *ready_list = (ParallelReadyList *) callback_data;

	pg_log_info("finished item %d %s %s",
				te->dumpId, te->desc, te->tag);

	if (status == WORKER_CREATE_DONE)
		mark_create_done(AH, te);
	else if (status == WORKER_INHIBIT_DATA)
	{
		inhibit_data_for_failed_table(AH, te);
		AH->public.n_errors++;
	}
	else if (status == WORKER_IGNORED_ERRORS)
		AH->public.n_errors++;
	else if (status != 0)
		fatal("worker process failed: exit code %d",
			  status);

	reduce_dependencies(AH, te, ready_list);
}