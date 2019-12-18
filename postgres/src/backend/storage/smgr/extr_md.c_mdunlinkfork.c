#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RelFileNodeBackend ;
typedef  scalar_t__ ForkNumber ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CloseTransientFile (int) ; 
 int ENOENT ; 
 scalar_t__ MAIN_FORKNUM ; 
 int O_RDWR ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 scalar_t__ RelFileNodeBackendIsTemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int errno ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  register_forget_request (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  register_unlink_segment (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* relpath (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
mdunlinkfork(RelFileNodeBackend rnode, ForkNumber forkNum, bool isRedo)
{
	char	   *path;
	int			ret;

	path = relpath(rnode, forkNum);

	/*
	 * Delete or truncate the first segment.
	 */
	if (isRedo || forkNum != MAIN_FORKNUM || RelFileNodeBackendIsTemp(rnode))
	{
		/* First, forget any pending sync requests for the first segment */
		if (!RelFileNodeBackendIsTemp(rnode))
			register_forget_request(rnode, forkNum, 0 /* first seg */ );

		/* Next unlink the file */
		ret = unlink(path);
		if (ret < 0 && errno != ENOENT)
			ereport(WARNING,
					(errcode_for_file_access(),
					 errmsg("could not remove file \"%s\": %m", path)));
	}
	else
	{
		/* truncate(2) would be easier here, but Windows hasn't got it */
		int			fd;

		fd = OpenTransientFile(path, O_RDWR | PG_BINARY);
		if (fd >= 0)
		{
			int			save_errno;

			ret = ftruncate(fd, 0);
			save_errno = errno;
			CloseTransientFile(fd);
			errno = save_errno;
		}
		else
			ret = -1;
		if (ret < 0 && errno != ENOENT)
			ereport(WARNING,
					(errcode_for_file_access(),
					 errmsg("could not truncate file \"%s\": %m", path)));

		/* Register request to unlink first segment later */
		register_unlink_segment(rnode, forkNum, 0 /* first seg */ );
	}

	/*
	 * Delete any additional segments.
	 */
	if (ret >= 0)
	{
		char	   *segpath = (char *) palloc(strlen(path) + 12);
		BlockNumber segno;

		/*
		 * Note that because we loop until getting ENOENT, we will correctly
		 * remove all inactive segments as well as active ones.
		 */
		for (segno = 1;; segno++)
		{
			/*
			 * Forget any pending sync requests for this segment before we try
			 * to unlink.
			 */
			if (!RelFileNodeBackendIsTemp(rnode))
				register_forget_request(rnode, forkNum, segno);

			sprintf(segpath, "%s.%u", path, segno);
			if (unlink(segpath) < 0)
			{
				/* ENOENT is expected after the last segment... */
				if (errno != ENOENT)
					ereport(WARNING,
							(errcode_for_file_access(),
							 errmsg("could not remove file \"%s\": %m", segpath)));
				break;
			}
		}
		pfree(segpath);
	}

	pfree(path);
}