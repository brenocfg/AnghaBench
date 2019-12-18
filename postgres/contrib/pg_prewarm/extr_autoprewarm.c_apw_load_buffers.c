#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_5__ {scalar_t__ pid_using_dumpfile; int prewarm_start_idx; int prewarm_stop_idx; int /*<<< orphan*/  prewarmed_blocks; int /*<<< orphan*/  lock; int /*<<< orphan*/  block_info_handle; scalar_t__ database; } ;
struct TYPE_4__ {scalar_t__ database; unsigned int forknum; int /*<<< orphan*/  blocknum; int /*<<< orphan*/  filenode; int /*<<< orphan*/  tablespace; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BlockInfoRecord ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOPREWARM_FILE ; 
 int /*<<< orphan*/ * AllocateFile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DSM_HANDLE_INVALID ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  apw_compare_blockinfo ; 
 int /*<<< orphan*/  apw_start_database_worker () ; 
 TYPE_3__* apw_state ; 
 int /*<<< orphan*/ * dsm_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,unsigned long,...) ; 
 scalar_t__ errno ; 
 int fscanf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  have_free_buffer () ; 
 int /*<<< orphan*/  pg_qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apw_load_buffers(void)
{
	FILE	   *file = NULL;
	int			num_elements,
				i;
	BlockInfoRecord *blkinfo;
	dsm_segment *seg;

	/*
	 * Skip the prewarm if the dump file is in use; otherwise, prevent any
	 * other process from writing it while we're using it.
	 */
	LWLockAcquire(&apw_state->lock, LW_EXCLUSIVE);
	if (apw_state->pid_using_dumpfile == InvalidPid)
		apw_state->pid_using_dumpfile = MyProcPid;
	else
	{
		LWLockRelease(&apw_state->lock);
		ereport(LOG,
				(errmsg("skipping prewarm because block dump file is being written by PID %lu",
						(unsigned long) apw_state->pid_using_dumpfile)));
		return;
	}
	LWLockRelease(&apw_state->lock);

	/*
	 * Open the block dump file.  Exit quietly if it doesn't exist, but report
	 * any other error.
	 */
	file = AllocateFile(AUTOPREWARM_FILE, "r");
	if (!file)
	{
		if (errno == ENOENT)
		{
			LWLockAcquire(&apw_state->lock, LW_EXCLUSIVE);
			apw_state->pid_using_dumpfile = InvalidPid;
			LWLockRelease(&apw_state->lock);
			return;				/* No file to load. */
		}
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read file \"%s\": %m",
						AUTOPREWARM_FILE)));
	}

	/* First line of the file is a record count. */
	if (fscanf(file, "<<%d>>\n", &num_elements) != 1)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read from file \"%s\": %m",
						AUTOPREWARM_FILE)));

	/* Allocate a dynamic shared memory segment to store the record data. */
	seg = dsm_create(sizeof(BlockInfoRecord) * num_elements, 0);
	blkinfo = (BlockInfoRecord *) dsm_segment_address(seg);

	/* Read records, one per line. */
	for (i = 0; i < num_elements; i++)
	{
		unsigned	forknum;

		if (fscanf(file, "%u,%u,%u,%u,%u\n", &blkinfo[i].database,
				   &blkinfo[i].tablespace, &blkinfo[i].filenode,
				   &forknum, &blkinfo[i].blocknum) != 5)
			ereport(ERROR,
					(errmsg("autoprewarm block dump file is corrupted at line %d",
							i + 1)));
		blkinfo[i].forknum = forknum;
	}

	FreeFile(file);

	/* Sort the blocks to be loaded. */
	pg_qsort(blkinfo, num_elements, sizeof(BlockInfoRecord),
			 apw_compare_blockinfo);

	/* Populate shared memory state. */
	apw_state->block_info_handle = dsm_segment_handle(seg);
	apw_state->prewarm_start_idx = apw_state->prewarm_stop_idx = 0;
	apw_state->prewarmed_blocks = 0;

	/* Get the info position of the first block of the next database. */
	while (apw_state->prewarm_start_idx < num_elements)
	{
		int			j = apw_state->prewarm_start_idx;
		Oid			current_db = blkinfo[j].database;

		/*
		 * Advance the prewarm_stop_idx to the first BlockInfoRecord that does
		 * not belong to this database.
		 */
		j++;
		while (j < num_elements)
		{
			if (current_db != blkinfo[j].database)
			{
				/*
				 * Combine BlockInfoRecords for global objects with those of
				 * the database.
				 */
				if (current_db != InvalidOid)
					break;
				current_db = blkinfo[j].database;
			}

			j++;
		}

		/*
		 * If we reach this point with current_db == InvalidOid, then only
		 * BlockInfoRecords belonging to global objects exist.  We can't
		 * prewarm without a database connection, so just bail out.
		 */
		if (current_db == InvalidOid)
			break;

		/* Configure stop point and database for next per-database worker. */
		apw_state->prewarm_stop_idx = j;
		apw_state->database = current_db;
		Assert(apw_state->prewarm_start_idx < apw_state->prewarm_stop_idx);

		/* If we've run out of free buffers, don't launch another worker. */
		if (!have_free_buffer())
			break;

		/*
		 * Start a per-database worker to load blocks for this database; this
		 * function will return once the per-database worker exits.
		 */
		apw_start_database_worker();

		/* Prepare for next database. */
		apw_state->prewarm_start_idx = apw_state->prewarm_stop_idx;
	}

	/* Clean up. */
	dsm_detach(seg);
	LWLockAcquire(&apw_state->lock, LW_EXCLUSIVE);
	apw_state->block_info_handle = DSM_HANDLE_INVALID;
	apw_state->pid_using_dumpfile = InvalidPid;
	LWLockRelease(&apw_state->lock);

	/* Report our success. */
	ereport(LOG,
			(errmsg("autoprewarm successfully prewarmed %d of %d previously-loaded blocks",
					apw_state->prewarmed_blocks, num_elements)));
}