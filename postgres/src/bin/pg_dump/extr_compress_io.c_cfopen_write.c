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
typedef  int /*<<< orphan*/  cfp ;

/* Variables and functions */
 int /*<<< orphan*/ * cfopen (char const*,char const*,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free_keep_errno (char*) ; 
 char* psprintf (char*,char const*) ; 

cfp *
cfopen_write(const char *path, const char *mode, int compression)
{
	cfp		   *fp;

	if (compression == 0)
		fp = cfopen(path, mode, 0);
	else
	{
#ifdef HAVE_LIBZ
		char	   *fname;

		fname = psprintf("%s.gz", path);
		fp = cfopen(fname, mode, compression);
		free_keep_errno(fname);
#else
		fatal("not built with zlib support");
		fp = NULL;				/* keep compiler quiet */
#endif
	}
	return fp;
}