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
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendStringLiteral (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fmtId (char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  parsePGArray (char const*,char***,int*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool
appendReloptionsArray(PQExpBuffer buffer, const char *reloptions,
					  const char *prefix, int encoding, bool std_strings)
{
	char	  **options;
	int			noptions;
	int			i;

	if (!parsePGArray(reloptions, &options, &noptions))
	{
		if (options)
			free(options);
		return false;
	}

	for (i = 0; i < noptions; i++)
	{
		char	   *option = options[i];
		char	   *name;
		char	   *separator;
		char	   *value;

		/*
		 * Each array element should have the form name=value.  If the "=" is
		 * missing for some reason, treat it like an empty value.
		 */
		name = option;
		separator = strchr(option, '=');
		if (separator)
		{
			*separator = '\0';
			value = separator + 1;
		}
		else
			value = "";

		if (i > 0)
			appendPQExpBufferStr(buffer, ", ");
		appendPQExpBuffer(buffer, "%s%s=", prefix, fmtId(name));

		/*
		 * In general we need to quote the value; but to avoid unnecessary
		 * clutter, do not quote if it is an identifier that would not need
		 * quoting.  (We could also allow numbers, but that is a bit trickier
		 * than it looks --- for example, are leading zeroes significant?  We
		 * don't want to assume very much here about what custom reloptions
		 * might mean.)
		 */
		if (strcmp(fmtId(value), value) == 0)
			appendPQExpBufferStr(buffer, value);
		else
			appendStringLiteral(buffer, value, encoding, std_strings);
	}

	if (options)
		free(options);

	return true;
}