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
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static char *
constructConnStr(const char **keywords, const char **values)
{
	PQExpBuffer buf = createPQExpBuffer();
	char	   *connstr;
	int			i;
	bool		firstkeyword = true;

	/* Construct a new connection string in key='value' format. */
	for (i = 0; keywords[i] != NULL; i++)
	{
		if (strcmp(keywords[i], "dbname") == 0 ||
			strcmp(keywords[i], "password") == 0 ||
			strcmp(keywords[i], "fallback_application_name") == 0)
			continue;

		if (!firstkeyword)
			appendPQExpBufferChar(buf, ' ');
		firstkeyword = false;
		appendPQExpBuffer(buf, "%s=", keywords[i]);
		appendConnStrVal(buf, values[i]);
	}

	connstr = pg_strdup(buf->data);
	destroyPQExpBuffer(buf);
	return connstr;
}