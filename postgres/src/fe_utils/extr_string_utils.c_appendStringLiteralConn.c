#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 char ESCAPE_STRING_SYNTAX ; 
 int /*<<< orphan*/  PQclientEncoding (int /*<<< orphan*/ *) ; 
 scalar_t__ PQescapeStringConn (int /*<<< orphan*/ *,char*,char const*,size_t,int /*<<< orphan*/ *) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringLiteral (TYPE_1__*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enlargePQExpBuffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

void
appendStringLiteralConn(PQExpBuffer buf, const char *str, PGconn *conn)
{
	size_t		length = strlen(str);

	/*
	 * XXX This is a kluge to silence escape_string_warning in our utility
	 * programs.  It should go away someday.
	 */
	if (strchr(str, '\\') != NULL && PQserverVersion(conn) >= 80100)
	{
		/* ensure we are not adjacent to an identifier */
		if (buf->len > 0 && buf->data[buf->len - 1] != ' ')
			appendPQExpBufferChar(buf, ' ');
		appendPQExpBufferChar(buf, ESCAPE_STRING_SYNTAX);
		appendStringLiteral(buf, str, PQclientEncoding(conn), false);
		return;
	}
	/* XXX end kluge */

	if (!enlargePQExpBuffer(buf, 2 * length + 2))
		return;
	appendPQExpBufferChar(buf, '\'');
	buf->len += PQescapeStringConn(conn, buf->data + buf->len,
								   str, length, NULL);
	appendPQExpBufferChar(buf, '\'');
}