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
struct TYPE_5__ {scalar_t__ lo_buf_used; int loFd; scalar_t__ connection; scalar_t__ writingBlob; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ahprintf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dump_lo_buf (TYPE_1__*) ; 
 int /*<<< orphan*/  lo_close (scalar_t__,int) ; 

void
EndRestoreBlob(ArchiveHandle *AH, Oid oid)
{
	if (AH->lo_buf_used > 0)
	{
		/* Write remaining bytes from the LO buffer */
		dump_lo_buf(AH);
	}

	AH->writingBlob = 0;

	if (AH->connection)
	{
		lo_close(AH->connection, AH->loFd);
		AH->loFd = -1;
	}
	else
	{
		ahprintf(AH, "SELECT pg_catalog.lo_close(0);\n\n");
	}
}