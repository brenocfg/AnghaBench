#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mode_compression ;
struct TYPE_5__ {int /*<<< orphan*/ * uncompressedfp; int /*<<< orphan*/ * compressedfp; } ;
typedef  TYPE_1__ cfp ;

/* Variables and functions */
 int Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  free_keep_errno (TYPE_1__*) ; 
 void* gzopen (char const*,char const*) ; 
 TYPE_1__* pg_malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

cfp *
cfopen(const char *path, const char *mode, int compression)
{
	cfp		   *fp = pg_malloc(sizeof(cfp));

	if (compression != 0)
	{
#ifdef HAVE_LIBZ
		if (compression != Z_DEFAULT_COMPRESSION)
		{
			/* user has specified a compression level, so tell zlib to use it */
			char		mode_compression[32];

			snprintf(mode_compression, sizeof(mode_compression), "%s%d",
					 mode, compression);
			fp->compressedfp = gzopen(path, mode_compression);
		}
		else
		{
			/* don't specify a level, just use the zlib default */
			fp->compressedfp = gzopen(path, mode);
		}

		fp->uncompressedfp = NULL;
		if (fp->compressedfp == NULL)
		{
			free_keep_errno(fp);
			fp = NULL;
		}
#else
		fatal("not built with zlib support");
#endif
	}
	else
	{
#ifdef HAVE_LIBZ
		fp->compressedfp = NULL;
#endif
		fp->uncompressedfp = fopen(path, mode);
		if (fp->uncompressedfp == NULL)
		{
			free_keep_errno(fp);
			fp = NULL;
		}
	}

	return fp;
}