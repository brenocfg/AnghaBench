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
struct TYPE_2__ {scalar_t__ extent; int gc_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  n_writers; } ;
typedef  TYPE_1__ pgssSharedState ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  CloseTransientFile (int) ; 
 int /*<<< orphan*/  LOG ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int OpenTransientFile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PGSS_TEXT_FILE ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pgss ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static bool
qtext_store(const char *query, int query_len,
			Size *query_offset, int *gc_count)
{
	Size		off;
	int			fd;

	/*
	 * We use a spinlock to protect extent/n_writers/gc_count, so that
	 * multiple processes may execute this function concurrently.
	 */
	{
		volatile pgssSharedState *s = (volatile pgssSharedState *) pgss;

		SpinLockAcquire(&s->mutex);
		off = s->extent;
		s->extent += query_len + 1;
		s->n_writers++;
		if (gc_count)
			*gc_count = s->gc_count;
		SpinLockRelease(&s->mutex);
	}

	*query_offset = off;

	/* Now write the data into the successfully-reserved part of the file */
	fd = OpenTransientFile(PGSS_TEXT_FILE, O_RDWR | O_CREAT | PG_BINARY);
	if (fd < 0)
		goto error;

	if (lseek(fd, off, SEEK_SET) != off)
		goto error;

	if (write(fd, query, query_len) != query_len)
		goto error;
	if (write(fd, "\0", 1) != 1)
		goto error;

	CloseTransientFile(fd);

	/* Mark our write complete */
	{
		volatile pgssSharedState *s = (volatile pgssSharedState *) pgss;

		SpinLockAcquire(&s->mutex);
		s->n_writers--;
		SpinLockRelease(&s->mutex);
	}

	return true;

error:
	ereport(LOG,
			(errcode_for_file_access(),
			 errmsg("could not write file \"%s\": %m",
					PGSS_TEXT_FILE)));

	if (fd >= 0)
		CloseTransientFile(fd);

	/* Mark our write complete */
	{
		volatile pgssSharedState *s = (volatile pgssSharedState *) pgss;

		SpinLockAcquire(&s->mutex);
		s->n_writers--;
		SpinLockRelease(&s->mutex);
	}

	return false;
}