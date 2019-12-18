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
typedef  int /*<<< orphan*/ * gzFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_gz_error (int /*<<< orphan*/ *) ; 
 int gzwrite (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,...) ; 

__attribute__((used)) static void
writeTarData(
#ifdef HAVE_LIBZ
			 gzFile ztarfile,
#endif
			 FILE *tarfile, char *buf, int r, char *current_file)
{
#ifdef HAVE_LIBZ
	if (ztarfile != NULL)
	{
		if (gzwrite(ztarfile, buf, r) != r)
		{
			pg_log_error("could not write to compressed file \"%s\": %s",
						 current_file, get_gz_error(ztarfile));
			exit(1);
		}
	}
	else
#endif
	{
		if (fwrite(buf, r, 1, tarfile) != 1)
		{
			pg_log_error("could not write to file \"%s\": %m", current_file);
			exit(1);
		}
	}
}