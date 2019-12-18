#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ outCount; scalar_t__ Pfdebug; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int pqSendSome (TYPE_1__*,scalar_t__) ; 

int
pqFlush(PGconn *conn)
{
	if (conn->Pfdebug)
		fflush(conn->Pfdebug);

	if (conn->outCount > 0)
		return pqSendSome(conn, conn->outCount);

	return 0;
}