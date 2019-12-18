#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  public; int /*<<< orphan*/  (* SetupWorkerPtr ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int pipeRevRead; int pipeRevWrite; } ;
typedef  TYPE_1__ ParallelSlot ;
typedef  TYPE_2__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 TYPE_2__* CloneArchive (TYPE_2__*) ; 
 int /*<<< orphan*/  DeCloneArchive (TYPE_2__*) ; 
 int /*<<< orphan*/  DisconnectDatabase (int /*<<< orphan*/ *) ; 
 size_t PIPE_READ ; 
 size_t PIPE_WRITE ; 
 int /*<<< orphan*/  WaitForCommands (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  set_cancel_slot_archive (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RunWorker(ArchiveHandle *AH, ParallelSlot *slot)
{
	int			pipefd[2];

	/* fetch child ends of pipes */
	pipefd[PIPE_READ] = slot->pipeRevRead;
	pipefd[PIPE_WRITE] = slot->pipeRevWrite;

	/*
	 * Clone the archive so that we have our own state to work with, and in
	 * particular our own database connection.
	 *
	 * We clone on Unix as well as Windows, even though technically we don't
	 * need to because fork() gives us a copy in our own address space
	 * already.  But CloneArchive resets the state information and also clones
	 * the database connection which both seem kinda helpful.
	 */
	AH = CloneArchive(AH);

	/* Remember cloned archive where signal handler can find it */
	set_cancel_slot_archive(slot, AH);

	/*
	 * Call the setup worker function that's defined in the ArchiveHandle.
	 */
	(AH->SetupWorkerPtr) ((Archive *) AH);

	/*
	 * Execute commands until done.
	 */
	WaitForCommands(AH, pipefd);

	/*
	 * Disconnect from database and clean up.
	 */
	set_cancel_slot_archive(slot, NULL);
	DisconnectDatabase(&(AH->public));
	DeCloneArchive(AH);
}