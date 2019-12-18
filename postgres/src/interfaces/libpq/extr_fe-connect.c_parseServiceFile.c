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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {char* keyword; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXBUFSIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int ldapServiceLookup (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int
parseServiceFile(const char *serviceFile,
				 const char *service,
				 PQconninfoOption *options,
				 PQExpBuffer errorMessage,
				 bool *group_found)
{
	int			linenr = 0,
				i;
	FILE	   *f;
	char		buf[MAXBUFSIZE],
			   *line;

	f = fopen(serviceFile, "r");
	if (f == NULL)
	{
		printfPQExpBuffer(errorMessage, libpq_gettext("service file \"%s\" not found\n"),
						  serviceFile);
		return 1;
	}

	while ((line = fgets(buf, sizeof(buf), f)) != NULL)
	{
		int			len;

		linenr++;

		if (strlen(line) >= sizeof(buf) - 1)
		{
			fclose(f);
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("line %d too long in service file \"%s\"\n"),
							  linenr,
							  serviceFile);
			return 2;
		}

		/* ignore whitespace at end of line, especially the newline */
		len = strlen(line);
		while (len > 0 && isspace((unsigned char) line[len - 1]))
			line[--len] = '\0';

		/* ignore leading whitespace too */
		while (*line && isspace((unsigned char) line[0]))
			line++;

		/* ignore comments and empty lines */
		if (line[0] == '\0' || line[0] == '#')
			continue;

		/* Check for right groupname */
		if (line[0] == '[')
		{
			if (*group_found)
			{
				/* group info already read */
				fclose(f);
				return 0;
			}

			if (strncmp(line + 1, service, strlen(service)) == 0 &&
				line[strlen(service) + 1] == ']')
				*group_found = true;
			else
				*group_found = false;
		}
		else
		{
			if (*group_found)
			{
				/*
				 * Finally, we are in the right group and can parse the line
				 */
				char	   *key,
						   *val;
				bool		found_keyword;

#ifdef USE_LDAP
				if (strncmp(line, "ldap", 4) == 0)
				{
					int			rc = ldapServiceLookup(line, options, errorMessage);

					/* if rc = 2, go on reading for fallback */
					switch (rc)
					{
						case 0:
							fclose(f);
							return 0;
						case 1:
						case 3:
							fclose(f);
							return 3;
						case 2:
							continue;
					}
				}
#endif

				key = line;
				val = strchr(line, '=');
				if (val == NULL)
				{
					printfPQExpBuffer(errorMessage,
									  libpq_gettext("syntax error in service file \"%s\", line %d\n"),
									  serviceFile,
									  linenr);
					fclose(f);
					return 3;
				}
				*val++ = '\0';

				if (strcmp(key, "service") == 0)
				{
					printfPQExpBuffer(errorMessage,
									  libpq_gettext("nested service specifications not supported in service file \"%s\", line %d\n"),
									  serviceFile,
									  linenr);
					fclose(f);
					return 3;
				}

				/*
				 * Set the parameter --- but don't override any previous
				 * explicit setting.
				 */
				found_keyword = false;
				for (i = 0; options[i].keyword; i++)
				{
					if (strcmp(options[i].keyword, key) == 0)
					{
						if (options[i].val == NULL)
							options[i].val = strdup(val);
						if (!options[i].val)
						{
							printfPQExpBuffer(errorMessage,
											  libpq_gettext("out of memory\n"));
							fclose(f);
							return 3;
						}
						found_keyword = true;
						break;
					}
				}

				if (!found_keyword)
				{
					printfPQExpBuffer(errorMessage,
									  libpq_gettext("syntax error in service file \"%s\", line %d\n"),
									  serviceFile,
									  linenr);
					fclose(f);
					return 3;
				}
			}
		}
	}

	fclose(f);

	return 0;
}