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
struct TYPE_3__ {int /*<<< orphan*/ * next_result; int /*<<< orphan*/ * result; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 

void
pqClearAsyncResult(PGconn *conn)
{
	if (conn->result)
		PQclear(conn->result);
	conn->result = NULL;
	if (conn->next_result)
		PQclear(conn->next_result);
	conn->next_result = NULL;
}