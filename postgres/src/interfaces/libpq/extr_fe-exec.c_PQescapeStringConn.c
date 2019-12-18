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
struct TYPE_4__ {int /*<<< orphan*/  std_strings; int /*<<< orphan*/  client_encoding; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 size_t PQescapeStringInternal (TYPE_1__*,char*,char const*,size_t,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t
PQescapeStringConn(PGconn *conn,
				   char *to, const char *from, size_t length,
				   int *error)
{
	if (!conn)
	{
		/* force empty-string result */
		*to = '\0';
		if (error)
			*error = 1;
		return 0;
	}
	return PQescapeStringInternal(conn, to, from, length, error,
								  conn->client_encoding,
								  conn->std_strings);
}