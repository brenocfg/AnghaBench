#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t filePos; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_6__ {int /*<<< orphan*/  FH; scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 size_t ReadInt (TYPE_2__*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pg_malloc (size_t) ; 

__attribute__((used)) static void
_skipData(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	size_t		blkLen;
	char	   *buf = NULL;
	int			buflen = 0;
	size_t		cnt;

	blkLen = ReadInt(AH);
	while (blkLen != 0)
	{
		if (blkLen > buflen)
		{
			if (buf)
				free(buf);
			buf = (char *) pg_malloc(blkLen);
			buflen = blkLen;
		}
		if ((cnt = fread(buf, 1, blkLen, AH->FH)) != blkLen)
		{
			if (feof(AH->FH))
				fatal("could not read from input file: end of file");
			else
				fatal("could not read from input file: %m");
		}

		ctx->filePos += blkLen;

		blkLen = ReadInt(AH);
	}

	if (buf)
		free(buf);
}