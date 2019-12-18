#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_3__ {int /*<<< orphan*/ * connection; scalar_t__ connCancel; } ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 scalar_t__ PQTRANS_ACTIVE ; 
 int /*<<< orphan*/  PQcancel (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_archive_cancel_info (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
DisconnectDatabase(Archive *AHX)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	char		errbuf[1];

	if (!AH->connection)
		return;

	if (AH->connCancel)
	{
		/*
		 * If we have an active query, send a cancel before closing, ignoring
		 * any errors.  This is of no use for a normal exit, but might be
		 * helpful during fatal().
		 */
		if (PQtransactionStatus(AH->connection) == PQTRANS_ACTIVE)
			(void) PQcancel(AH->connCancel, errbuf, sizeof(errbuf));

		/*
		 * Prevent signal handler from sending a cancel after this.
		 */
		set_archive_cancel_info(AH, NULL);
	}

	PQfinish(AH->connection);
	AH->connection = NULL;
}