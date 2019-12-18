#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; void* len; int /*<<< orphan*/  maxlen; } ;
struct TYPE_5__ {scalar_t__ sock; TYPE_1__ errorMessage; int /*<<< orphan*/  be_key; int /*<<< orphan*/  be_pid; int /*<<< orphan*/  raddr; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ PGINVALID_SOCKET ; 
 int internal_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* strlen (int /*<<< orphan*/ ) ; 

int
PQrequestCancel(PGconn *conn)
{
	int			r;

	/* Check we have an open connection */
	if (!conn)
		return false;

	if (conn->sock == PGINVALID_SOCKET)
	{
		strlcpy(conn->errorMessage.data,
				"PQrequestCancel() -- connection is not open\n",
				conn->errorMessage.maxlen);
		conn->errorMessage.len = strlen(conn->errorMessage.data);

		return false;
	}

	r = internal_cancel(&conn->raddr, conn->be_pid, conn->be_key,
						conn->errorMessage.data, conn->errorMessage.maxlen);

	if (!r)
		conn->errorMessage.len = strlen(conn->errorMessage.data);

	return r;
}