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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  PostgresPollingStatusType ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PGRES_POLLING_FAILED ; 
 int /*<<< orphan*/  PGRES_POLLING_OK ; 
 int /*<<< orphan*/  PGRES_POLLING_READING ; 
 scalar_t__ errno ; 
 int pqReadReady (int /*<<< orphan*/ *) ; 
 scalar_t__ pqsecure_raw_read (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static PostgresPollingStatusType
gss_read(PGconn *conn, void *recv_buffer, size_t length, ssize_t *ret)
{
	*ret = pqsecure_raw_read(conn, recv_buffer, length);
	if (*ret < 0 && errno == EWOULDBLOCK)
		return PGRES_POLLING_READING;
	else if (*ret < 0)
		return PGRES_POLLING_FAILED;

	/* Check for EOF */
	if (*ret == 0)
	{
		int			result = pqReadReady(conn);

		if (result < 0)
			return PGRES_POLLING_FAILED;

		if (!result)
			return PGRES_POLLING_READING;

		*ret = pqsecure_raw_read(conn, recv_buffer, length);
		if (*ret == 0)
			return PGRES_POLLING_FAILED;
	}

	return PGRES_POLLING_OK;
}