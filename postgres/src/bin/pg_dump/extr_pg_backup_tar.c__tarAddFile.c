#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t pgoff_t ;
struct TYPE_7__ {size_t tarFHpos; } ;
typedef  TYPE_1__ lclContext ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {scalar_t__ formatData; } ;
struct TYPE_8__ {scalar_t__ fileLen; int /*<<< orphan*/  tarFH; int /*<<< orphan*/ * tmpFH; } ;
typedef  TYPE_2__ TAR_MEMBER ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ EOF ; 
 char* INT64_FORMAT ; 
 int /*<<< orphan*/  READ_ERROR_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WRITE_ERROR_EXIT ; 
 int /*<<< orphan*/  _tarWriteHeader (TYPE_2__*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ ) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_tarAddFile(ArchiveHandle *AH, TAR_MEMBER *th)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	FILE	   *tmp = th->tmpFH;	/* Grab it for convenience */
	char		buf[32768];
	size_t		cnt;
	pgoff_t		len = 0;
	size_t		res;
	size_t		i,
				pad;

	/*
	 * Find file len & go back to start.
	 */
	fseeko(tmp, 0, SEEK_END);
	th->fileLen = ftello(tmp);
	if (th->fileLen < 0)
		fatal("could not determine seek position in archive file: %m");
	fseeko(tmp, 0, SEEK_SET);

	_tarWriteHeader(th);

	while ((cnt = fread(buf, 1, sizeof(buf), tmp)) > 0)
	{
		if ((res = fwrite(buf, 1, cnt, th->tarFH)) != cnt)
			WRITE_ERROR_EXIT;
		len += res;
	}
	if (!feof(tmp))
		READ_ERROR_EXIT(tmp);

	if (fclose(tmp) != 0)		/* This *should* delete it... */
		fatal("could not close temporary file: %m");

	if (len != th->fileLen)
	{
		char		buf1[32],
					buf2[32];

		snprintf(buf1, sizeof(buf1), INT64_FORMAT, (int64) len);
		snprintf(buf2, sizeof(buf2), INT64_FORMAT, (int64) th->fileLen);
		fatal("actual file length (%s) does not match expected (%s)",
			  buf1, buf2);
	}

	pad = ((len + 511) & ~511) - len;
	for (i = 0; i < pad; i++)
	{
		if (fputc('\0', th->tarFH) == EOF)
			WRITE_ERROR_EXIT;
	}

	ctx->tarFHpos += len + pad;
}