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
struct TYPE_5__ {scalar_t__ version; int loFd; int writingBlob; scalar_t__ connection; scalar_t__ lo_buf_used; int /*<<< orphan*/  blobCount; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  DropBlobIfExists (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  INV_WRITE ; 
 scalar_t__ K_VERS_1_12 ; 
 int /*<<< orphan*/  PQerrorMessage (scalar_t__) ; 
 int /*<<< orphan*/  ahprintf (TYPE_1__*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lo_create (scalar_t__,scalar_t__) ; 
 int lo_open (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_info (char*,scalar_t__) ; 

void
StartRestoreBlob(ArchiveHandle *AH, Oid oid, bool drop)
{
	bool		old_blob_style = (AH->version < K_VERS_1_12);
	Oid			loOid;

	AH->blobCount++;

	/* Initialize the LO Buffer */
	AH->lo_buf_used = 0;

	pg_log_info("restoring large object with OID %u", oid);

	/* With an old archive we must do drop and create logic here */
	if (old_blob_style && drop)
		DropBlobIfExists(AH, oid);

	if (AH->connection)
	{
		if (old_blob_style)
		{
			loOid = lo_create(AH->connection, oid);
			if (loOid == 0 || loOid != oid)
				fatal("could not create large object %u: %s",
					  oid, PQerrorMessage(AH->connection));
		}
		AH->loFd = lo_open(AH->connection, oid, INV_WRITE);
		if (AH->loFd == -1)
			fatal("could not open large object %u: %s",
				  oid, PQerrorMessage(AH->connection));
	}
	else
	{
		if (old_blob_style)
			ahprintf(AH, "SELECT pg_catalog.lo_open(pg_catalog.lo_create('%u'), %d);\n",
					 oid, INV_WRITE);
		else
			ahprintf(AH, "SELECT pg_catalog.lo_open('%u', %d);\n",
					 oid, INV_WRITE);
	}

	AH->writingBlob = 1;
}