#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t tarFHpos; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_8__ {size_t lookaheadLen; size_t lookaheadPos; size_t lookahead; scalar_t__ formatData; } ;
struct TYPE_7__ {int /*<<< orphan*/ * nFH; int /*<<< orphan*/  zFH; } ;
typedef  TYPE_2__ TAR_MEMBER ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  GZEOF (int /*<<< orphan*/ ) ; 
 size_t GZREAD (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ERROR_EXIT (int /*<<< orphan*/ *) ; 
 int Z_ERRNO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 char* gzerror (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
_tarReadRaw(ArchiveHandle *AH, void *buf, size_t len, TAR_MEMBER *th, FILE *fh)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	size_t		avail;
	size_t		used = 0;
	size_t		res = 0;

	avail = AH->lookaheadLen - AH->lookaheadPos;
	if (avail > 0)
	{
		/* We have some lookahead bytes to use */
		if (avail >= len)		/* Just use the lookahead buffer */
			used = len;
		else
			used = avail;

		/* Copy, and adjust buffer pos */
		memcpy(buf, AH->lookahead + AH->lookaheadPos, used);
		AH->lookaheadPos += used;

		/* Adjust required length */
		len -= used;
	}

	/* Read the file if len > 0 */
	if (len > 0)
	{
		if (fh)
		{
			res = fread(&((char *) buf)[used], 1, len, fh);
			if (res != len && !feof(fh))
				READ_ERROR_EXIT(fh);
		}
		else if (th)
		{
			if (th->zFH)
			{
				res = GZREAD(&((char *) buf)[used], 1, len, th->zFH);
				if (res != len && !GZEOF(th->zFH))
				{
#ifdef HAVE_LIBZ
					int			errnum;
					const char *errmsg = gzerror(th->zFH, &errnum);

					fatal("could not read from input file: %s",
						  errnum == Z_ERRNO ? strerror(errno) : errmsg);
#else
					fatal("could not read from input file: %s",
						  strerror(errno));
#endif
				}
			}
			else
			{
				res = fread(&((char *) buf)[used], 1, len, th->nFH);
				if (res != len && !feof(th->nFH))
					READ_ERROR_EXIT(th->nFH);
			}
		}
		else
			fatal("internal error -- neither th nor fh specified in _tarReadRaw()");
	}

	ctx->tarFHpos += res + used;

	return (res + used);
}