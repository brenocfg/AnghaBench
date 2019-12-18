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
struct TYPE_5__ {int filePos; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_6__ {scalar_t__ version; int /*<<< orphan*/  FH; scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int BLK_DATA ; 
 int EOF ; 
 scalar_t__ K_VERS_1_3 ; 
 int ReadInt (TYPE_2__*) ; 
 int getc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_readBlockHeader(ArchiveHandle *AH, int *type, int *id)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	int			byt;

	/*
	 * Note: if we are at EOF with a pre-1.3 input file, we'll fatal() inside
	 * ReadInt rather than returning EOF.  It doesn't seem worth jumping
	 * through hoops to deal with that case better, because no such files are
	 * likely to exist in the wild: only some 7.1 development versions of
	 * pg_dump ever generated such files.
	 */
	if (AH->version < K_VERS_1_3)
		*type = BLK_DATA;
	else
	{
		byt = getc(AH->FH);
		*type = byt;
		if (byt == EOF)
		{
			*id = 0;			/* don't return an uninitialized value */
			return;
		}
		ctx->filePos += 1;
	}

	*id = ReadInt(AH);
}