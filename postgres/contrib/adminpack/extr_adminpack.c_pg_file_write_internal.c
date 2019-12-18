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
typedef  int /*<<< orphan*/  text ;
struct stat {int dummy; } ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_FILE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 scalar_t__ VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 char* convert_and_check_filename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int64
pg_file_write_internal(text *file, text *data, bool replace)
{
	FILE	   *f;
	char	   *filename;
	int64		count = 0;

	filename = convert_and_check_filename(file, false);

	if (!replace)
	{
		struct stat fst;

		if (stat(filename, &fst) >= 0)
			ereport(ERROR,
					(ERRCODE_DUPLICATE_FILE,
					 errmsg("file \"%s\" exists", filename)));

		f = AllocateFile(filename, "wb");
	}
	else
		f = AllocateFile(filename, "ab");

	if (!f)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\" for writing: %m",
						filename)));

	count = fwrite(VARDATA_ANY(data), 1, VARSIZE_ANY_EXHDR(data), f);
	if (count != VARSIZE_ANY_EXHDR(data) || FreeFile(f))
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not write file \"%s\": %m", filename)));

	return (count);
}