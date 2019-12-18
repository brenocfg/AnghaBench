#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * tarFH; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_11__ {int compression; scalar_t__ formatData; } ;
struct TYPE_10__ {char mode; int /*<<< orphan*/ * tarFH; int /*<<< orphan*/  targetFile; TYPE_3__* AH; int /*<<< orphan*/ * tmpFH; int /*<<< orphan*/ * nFH; int /*<<< orphan*/ * zFH; } ;
typedef  TYPE_2__ TAR_MEMBER ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int O_TEMPORARY ; 
 int S_IRUSR ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IWUSR ; 
 TYPE_2__* _tarPositionTo (TYPE_3__*,char const*) ; 
 char* _tempnam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * gzdopen (int /*<<< orphan*/ ,char*) ; 
 int open (char*,int,int) ; 
 TYPE_2__* pg_malloc0 (int) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ * tmpfile () ; 
 int umask (int) ; 

__attribute__((used)) static TAR_MEMBER *
tarOpen(ArchiveHandle *AH, const char *filename, char mode)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	TAR_MEMBER *tm;

#ifdef HAVE_LIBZ
	char		fmode[14];
#endif

	if (mode == 'r')
	{
		tm = _tarPositionTo(AH, filename);
		if (!tm)				/* Not found */
		{
			if (filename)
			{
				/*
				 * Couldn't find the requested file. Future: do SEEK(0) and
				 * retry.
				 */
				fatal("could not find file \"%s\" in archive", filename);
			}
			else
			{
				/* Any file OK, none left, so return NULL */
				return NULL;
			}
		}

#ifdef HAVE_LIBZ

		if (AH->compression == 0)
			tm->nFH = ctx->tarFH;
		else
			fatal("compression is not supported by tar archive format");
		/* tm->zFH = gzdopen(dup(fileno(ctx->tarFH)), "rb"); */
#else
		tm->nFH = ctx->tarFH;
#endif
	}
	else
	{
		int			old_umask;

		tm = pg_malloc0(sizeof(TAR_MEMBER));

		/*
		 * POSIX does not require, but permits, tmpfile() to restrict file
		 * permissions.  Given an OS crash after we write data, the filesystem
		 * might retain the data but forget tmpfile()'s unlink().  If so, the
		 * file mode protects confidentiality of the data written.
		 */
		old_umask = umask(S_IRWXG | S_IRWXO);

#ifndef WIN32
		tm->tmpFH = tmpfile();
#else

		/*
		 * On WIN32, tmpfile() generates a filename in the root directory,
		 * which requires administrative permissions on certain systems. Loop
		 * until we find a unique file name we can create.
		 */
		while (1)
		{
			char	   *name;
			int			fd;

			name = _tempnam(NULL, "pg_temp_");
			if (name == NULL)
				break;
			fd = open(name, O_RDWR | O_CREAT | O_EXCL | O_BINARY |
					  O_TEMPORARY, S_IRUSR | S_IWUSR);
			free(name);

			if (fd != -1)		/* created a file */
			{
				tm->tmpFH = fdopen(fd, "w+b");
				break;
			}
			else if (errno != EEXIST)	/* failure other than file exists */
				break;
		}
#endif

		if (tm->tmpFH == NULL)
			fatal("could not generate temporary file name: %m");

		umask(old_umask);

#ifdef HAVE_LIBZ

		if (AH->compression != 0)
		{
			sprintf(fmode, "wb%d", AH->compression);
			tm->zFH = gzdopen(dup(fileno(tm->tmpFH)), fmode);
			if (tm->zFH == NULL)
				fatal("could not open temporary file");
		}
		else
			tm->nFH = tm->tmpFH;
#else

		tm->nFH = tm->tmpFH;
#endif

		tm->AH = AH;
		tm->targetFile = pg_strdup(filename);
	}

	tm->mode = mode;
	tm->tarFH = ctx->tarFH;

	return tm;
}