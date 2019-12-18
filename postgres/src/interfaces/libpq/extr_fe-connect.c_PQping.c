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
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  PGPing ;

/* Variables and functions */
 int /*<<< orphan*/ * PQconnectStart (char const*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internal_ping (int /*<<< orphan*/ *) ; 

PGPing
PQping(const char *conninfo)
{
	PGconn	   *conn = PQconnectStart(conninfo);
	PGPing		ret;

	ret = internal_ping(conn);
	PQfinish(conn);

	return ret;
}