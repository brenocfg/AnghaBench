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
typedef  int /*<<< orphan*/  PostgresPollingStatusType ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PGRES_POLLING_FAILED ; 
 int /*<<< orphan*/  pgtls_open_client (int /*<<< orphan*/ *) ; 

PostgresPollingStatusType
pqsecure_open_client(PGconn *conn)
{
#ifdef USE_SSL
	return pgtls_open_client(conn);
#else
	/* shouldn't get here */
	return PGRES_POLLING_FAILED;
#endif
}