#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_4__* FH; } ;
typedef  TYPE_3__ lclContext ;
struct TYPE_18__ {TYPE_1__* ropt; } ;
struct TYPE_21__ {TYPE_2__ public; scalar_t__ formatData; } ;
struct TYPE_20__ {int /*<<< orphan*/ * targetFile; } ;
struct TYPE_17__ {int /*<<< orphan*/  dropSchema; } ;
typedef  TYPE_4__ TAR_MEMBER ;
typedef  scalar_t__ Oid ;
typedef  TYPE_5__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EndRestoreBlob (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  EndRestoreBlobs (TYPE_5__*) ; 
 int /*<<< orphan*/  StartRestoreBlob (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartRestoreBlobs (TYPE_5__*) ; 
 int /*<<< orphan*/  ahwrite (char*,int,size_t,TYPE_5__*) ; 
 scalar_t__ atooid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_info (char*,scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tarClose (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* tarOpen (TYPE_5__*,int /*<<< orphan*/ *,char) ; 
 size_t tarRead (char*,int,TYPE_4__*) ; 

__attribute__((used)) static void
_LoadBlobs(ArchiveHandle *AH)
{
	Oid			oid;
	lclContext *ctx = (lclContext *) AH->formatData;
	TAR_MEMBER *th;
	size_t		cnt;
	bool		foundBlob = false;
	char		buf[4096];

	StartRestoreBlobs(AH);

	th = tarOpen(AH, NULL, 'r');	/* Open next file */
	while (th != NULL)
	{
		ctx->FH = th;

		if (strncmp(th->targetFile, "blob_", 5) == 0)
		{
			oid = atooid(&th->targetFile[5]);
			if (oid != 0)
			{
				pg_log_info("restoring large object with OID %u", oid);

				StartRestoreBlob(AH, oid, AH->public.ropt->dropSchema);

				while ((cnt = tarRead(buf, 4095, th)) > 0)
				{
					buf[cnt] = '\0';
					ahwrite(buf, 1, cnt, AH);
				}
				EndRestoreBlob(AH, oid);
				foundBlob = true;
			}
			tarClose(AH, th);
		}
		else
		{
			tarClose(AH, th);

			/*
			 * Once we have found the first blob, stop at the first non-blob
			 * entry (which will be 'blobs.toc').  This coding would eat all
			 * the rest of the archive if there are no blobs ... but this
			 * function shouldn't be called at all in that case.
			 */
			if (foundBlob)
				break;
		}

		th = tarOpen(AH, NULL, 'r');
	}
	EndRestoreBlobs(AH);
}