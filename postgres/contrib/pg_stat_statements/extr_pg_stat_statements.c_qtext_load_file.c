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
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 scalar_t__ CloseTransientFile (int) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ MaxAllocHugeSize ; 
 int O_RDONLY ; 
 int OpenTransientFile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PGSS_TEXT_FILE ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 

__attribute__((used)) static char *
qtext_load_file(Size *buffer_size)
{
	char	   *buf;
	int			fd;
	struct stat stat;

	fd = OpenTransientFile(PGSS_TEXT_FILE, O_RDONLY | PG_BINARY);
	if (fd < 0)
	{
		if (errno != ENOENT)
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							PGSS_TEXT_FILE)));
		return NULL;
	}

	/* Get file length */
	if (fstat(fd, &stat))
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not stat file \"%s\": %m",
						PGSS_TEXT_FILE)));
		CloseTransientFile(fd);
		return NULL;
	}

	/* Allocate buffer; beware that off_t might be wider than size_t */
	if (stat.st_size <= MaxAllocHugeSize)
		buf = (char *) malloc(stat.st_size);
	else
		buf = NULL;
	if (buf == NULL)
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory"),
				 errdetail("Could not allocate enough memory to read file \"%s\".",
						   PGSS_TEXT_FILE)));
		CloseTransientFile(fd);
		return NULL;
	}

	/*
	 * OK, slurp in the file.  If we get a short read and errno doesn't get
	 * set, the reason is probably that garbage collection truncated the file
	 * since we did the fstat(), so we don't log a complaint --- but we don't
	 * return the data, either, since it's most likely corrupt due to
	 * concurrent writes from garbage collection.
	 */
	errno = 0;
	if (read(fd, buf, stat.st_size) != stat.st_size)
	{
		if (errno)
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							PGSS_TEXT_FILE)));
		free(buf);
		CloseTransientFile(fd);
		return NULL;
	}

	if (CloseTransientFile(fd) != 0)
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not close file \"%s\": %m", PGSS_TEXT_FILE)));

	*buffer_size = stat.st_size;
	return buf;
}