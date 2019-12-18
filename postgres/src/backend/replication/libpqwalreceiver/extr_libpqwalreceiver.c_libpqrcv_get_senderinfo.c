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
struct TYPE_3__ {int /*<<< orphan*/ * streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* PQhost (int /*<<< orphan*/ *) ; 
 char* PQport (int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 char* pstrdup (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
libpqrcv_get_senderinfo(WalReceiverConn *conn, char **sender_host,
						int *sender_port)
{
	char	   *ret = NULL;

	*sender_host = NULL;
	*sender_port = 0;

	Assert(conn->streamConn != NULL);

	ret = PQhost(conn->streamConn);
	if (ret && strlen(ret) != 0)
		*sender_host = pstrdup(ret);

	ret = PQport(conn->streamConn);
	if (ret && strlen(ret) != 0)
		*sender_port = atoi(ret);
}