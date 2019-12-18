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
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  pversion; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 

int
PQprotocolVersion(const PGconn *conn)
{
	if (!conn)
		return 0;
	if (conn->status == CONNECTION_BAD)
		return 0;
	return PG_PROTOCOL_MAJOR(conn->pversion);
}