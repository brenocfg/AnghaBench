#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  PGcancel ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ PQTRANS_ACTIVE ; 
 int /*<<< orphan*/  PQcancel (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreeCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetCancel (int /*<<< orphan*/ *) ; 
 scalar_t__ PQtransactionStatus (int /*<<< orphan*/ *) ; 

void
disconnectDatabase(PGconn *conn)
{
	char		errbuf[256];

	Assert(conn != NULL);

	if (PQtransactionStatus(conn) == PQTRANS_ACTIVE)
	{
		PGcancel   *cancel;

		if ((cancel = PQgetCancel(conn)))
		{
			(void) PQcancel(cancel, errbuf, sizeof(errbuf));
			PQfreeCancel(cancel);
		}
	}

	PQfinish(conn);
}