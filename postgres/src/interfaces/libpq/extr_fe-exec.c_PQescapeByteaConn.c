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
struct TYPE_4__ {int sversion; int /*<<< orphan*/  std_strings; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 unsigned char* PQescapeByteaInternal (TYPE_1__*,unsigned char const*,size_t,size_t*,int /*<<< orphan*/ ,int) ; 

unsigned char *
PQescapeByteaConn(PGconn *conn,
				  const unsigned char *from, size_t from_length,
				  size_t *to_length)
{
	if (!conn)
		return NULL;
	return PQescapeByteaInternal(conn, from, from_length, to_length,
								 conn->std_strings,
								 (conn->sversion >= 90000));
}