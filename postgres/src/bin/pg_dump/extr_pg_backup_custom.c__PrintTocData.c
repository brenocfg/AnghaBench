#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ dataState; int /*<<< orphan*/  dataPos; } ;
typedef  TYPE_3__ lclTocEntry ;
struct TYPE_17__ {int /*<<< orphan*/  hasSeek; } ;
typedef  TYPE_4__ lclContext ;
struct TYPE_18__ {int dumpId; scalar_t__ formatData; } ;
typedef  TYPE_5__ TocEntry ;
struct TYPE_15__ {TYPE_1__* ropt; } ;
struct TYPE_19__ {TYPE_2__ public; int /*<<< orphan*/  FH; scalar_t__ formatData; } ;
struct TYPE_14__ {int /*<<< orphan*/  dropSchema; } ;
typedef  TYPE_6__ ArchiveHandle ;

/* Variables and functions */
#define  BLK_BLOBS 129 
#define  BLK_DATA 128 
 int EOF ; 
 scalar_t__ K_OFFSET_NO_DATA ; 
 scalar_t__ K_OFFSET_POS_NOT_SET ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _LoadBlobs (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PrintData (TYPE_6__*) ; 
 int /*<<< orphan*/  _readBlockHeader (TYPE_6__*,int*,int*) ; 
 int /*<<< orphan*/  _skipBlobs (TYPE_6__*) ; 
 int /*<<< orphan*/  _skipData (TYPE_6__*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_PrintTocData(ArchiveHandle *AH, TocEntry *te)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;
	int			blkType;
	int			id;

	if (tctx->dataState == K_OFFSET_NO_DATA)
		return;

	if (!ctx->hasSeek || tctx->dataState == K_OFFSET_POS_NOT_SET)
	{
		/*
		 * We cannot seek directly to the desired block.  Instead, skip over
		 * block headers until we find the one we want.  This could fail if we
		 * are asked to restore items out-of-order.
		 */
		_readBlockHeader(AH, &blkType, &id);

		while (blkType != EOF && id != te->dumpId)
		{
			switch (blkType)
			{
				case BLK_DATA:
					_skipData(AH);
					break;

				case BLK_BLOBS:
					_skipBlobs(AH);
					break;

				default:		/* Always have a default */
					fatal("unrecognized data block type (%d) while searching archive",
						  blkType);
					break;
			}
			_readBlockHeader(AH, &blkType, &id);
		}
	}
	else
	{
		/* We can just seek to the place we need to be. */
		if (fseeko(AH->FH, tctx->dataPos, SEEK_SET) != 0)
			fatal("error during file seek: %m");

		_readBlockHeader(AH, &blkType, &id);
	}

	/* Produce suitable failure message if we fell off end of file */
	if (blkType == EOF)
	{
		if (tctx->dataState == K_OFFSET_POS_NOT_SET)
			fatal("could not find block ID %d in archive -- "
				  "possibly due to out-of-order restore request, "
				  "which cannot be handled due to lack of data offsets in archive",
				  te->dumpId);
		else if (!ctx->hasSeek)
			fatal("could not find block ID %d in archive -- "
				  "possibly due to out-of-order restore request, "
				  "which cannot be handled due to non-seekable input file",
				  te->dumpId);
		else					/* huh, the dataPos led us to EOF? */
			fatal("could not find block ID %d in archive -- "
				  "possibly corrupt archive",
				  te->dumpId);
	}

	/* Are we sane? */
	if (id != te->dumpId)
		fatal("found unexpected block ID (%d) when reading data -- expected %d",
			  id, te->dumpId);

	switch (blkType)
	{
		case BLK_DATA:
			_PrintData(AH);
			break;

		case BLK_BLOBS:
			_LoadBlobs(AH, AH->public.ropt->dropSchema);
			break;

		default:				/* Always have a default */
			fatal("unrecognized data block type %d while restoring archive",
				  blkType);
			break;
	}
}