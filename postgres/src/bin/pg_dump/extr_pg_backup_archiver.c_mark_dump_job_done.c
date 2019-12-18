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
struct TYPE_3__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_1__ TocEntry ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_dump_job_done(ArchiveHandle *AH,
				   TocEntry *te,
				   int status,
				   void *callback_data)
{
	pg_log_info("finished item %d %s %s",
				te->dumpId, te->desc, te->tag);

	if (status != 0)
		fatal("worker process failed: exit code %d",
			  status);
}