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
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  bytea ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 scalar_t__ MaxAllocSize ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (scalar_t__) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static bytea *
read_binary_file(const char *filename, int64 seek_offset, int64 bytes_to_read,
				 bool missing_ok)
{
	bytea	   *buf;
	size_t		nbytes;
	FILE	   *file;

	if (bytes_to_read < 0)
	{
		if (seek_offset < 0)
			bytes_to_read = -seek_offset;
		else
		{
			struct stat fst;

			if (stat(filename, &fst) < 0)
			{
				if (missing_ok && errno == ENOENT)
					return NULL;
				else
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not stat file \"%s\": %m", filename)));
			}

			bytes_to_read = fst.st_size - seek_offset;
		}
	}

	/* not sure why anyone thought that int64 length was a good idea */
	if (bytes_to_read > (MaxAllocSize - VARHDRSZ))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("requested length too large")));

	if ((file = AllocateFile(filename, PG_BINARY_R)) == NULL)
	{
		if (missing_ok && errno == ENOENT)
			return NULL;
		else
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not open file \"%s\" for reading: %m",
							filename)));
	}

	if (fseeko(file, (off_t) seek_offset,
			   (seek_offset >= 0) ? SEEK_SET : SEEK_END) != 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not seek in file \"%s\": %m", filename)));

	buf = (bytea *) palloc((Size) bytes_to_read + VARHDRSZ);

	nbytes = fread(VARDATA(buf), 1, (size_t) bytes_to_read, file);

	if (ferror(file))
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read file \"%s\": %m", filename)));

	SET_VARSIZE(buf, nbytes + VARHDRSZ);

	FreeFile(file);

	return buf;
}