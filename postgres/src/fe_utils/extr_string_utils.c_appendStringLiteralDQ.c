#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  suffixes ;
struct TYPE_7__ {char const* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * strstr (char const*,char const*) ; 

void
appendStringLiteralDQ(PQExpBuffer buf, const char *str, const char *dqprefix)
{
	static const char suffixes[] = "_XXXXXXX";
	int			nextchar = 0;
	PQExpBuffer delimBuf = createPQExpBuffer();

	/* start with $ + dqprefix if not NULL */
	appendPQExpBufferChar(delimBuf, '$');
	if (dqprefix)
		appendPQExpBufferStr(delimBuf, dqprefix);

	/*
	 * Make sure we choose a delimiter which (without the trailing $) is not
	 * present in the string being quoted. We don't check with the trailing $
	 * because a string ending in $foo must not be quoted with $foo$.
	 */
	while (strstr(str, delimBuf->data) != NULL)
	{
		appendPQExpBufferChar(delimBuf, suffixes[nextchar++]);
		nextchar %= sizeof(suffixes) - 1;
	}

	/* add trailing $ */
	appendPQExpBufferChar(delimBuf, '$');

	/* quote it and we are all done */
	appendPQExpBufferStr(buf, delimBuf->data);
	appendPQExpBufferStr(buf, str);
	appendPQExpBufferStr(buf, delimBuf->data);

	destroyPQExpBuffer(delimBuf);
}