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
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  PQconninfoFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conninfo_add_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * conninfo_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conninfo_storeval (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static PQconninfoOption *
conninfo_parse(const char *conninfo, PQExpBuffer errorMessage,
			   bool use_defaults)
{
	char	   *pname;
	char	   *pval;
	char	   *buf;
	char	   *cp;
	char	   *cp2;
	PQconninfoOption *options;

	/* Make a working copy of PQconninfoOptions */
	options = conninfo_init(errorMessage);
	if (options == NULL)
		return NULL;

	/* Need a modifiable copy of the input string */
	if ((buf = strdup(conninfo)) == NULL)
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("out of memory\n"));
		PQconninfoFree(options);
		return NULL;
	}
	cp = buf;

	while (*cp)
	{
		/* Skip blanks before the parameter name */
		if (isspace((unsigned char) *cp))
		{
			cp++;
			continue;
		}

		/* Get the parameter name */
		pname = cp;
		while (*cp)
		{
			if (*cp == '=')
				break;
			if (isspace((unsigned char) *cp))
			{
				*cp++ = '\0';
				while (*cp)
				{
					if (!isspace((unsigned char) *cp))
						break;
					cp++;
				}
				break;
			}
			cp++;
		}

		/* Check that there is a following '=' */
		if (*cp != '=')
		{
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("missing \"=\" after \"%s\" in connection info string\n"),
							  pname);
			PQconninfoFree(options);
			free(buf);
			return NULL;
		}
		*cp++ = '\0';

		/* Skip blanks after the '=' */
		while (*cp)
		{
			if (!isspace((unsigned char) *cp))
				break;
			cp++;
		}

		/* Get the parameter value */
		pval = cp;

		if (*cp != '\'')
		{
			cp2 = pval;
			while (*cp)
			{
				if (isspace((unsigned char) *cp))
				{
					*cp++ = '\0';
					break;
				}
				if (*cp == '\\')
				{
					cp++;
					if (*cp != '\0')
						*cp2++ = *cp++;
				}
				else
					*cp2++ = *cp++;
			}
			*cp2 = '\0';
		}
		else
		{
			cp2 = pval;
			cp++;
			for (;;)
			{
				if (*cp == '\0')
				{
					printfPQExpBuffer(errorMessage,
									  libpq_gettext("unterminated quoted string in connection info string\n"));
					PQconninfoFree(options);
					free(buf);
					return NULL;
				}
				if (*cp == '\\')
				{
					cp++;
					if (*cp != '\0')
						*cp2++ = *cp++;
					continue;
				}
				if (*cp == '\'')
				{
					*cp2 = '\0';
					cp++;
					break;
				}
				*cp2++ = *cp++;
			}
		}

		/*
		 * Now that we have the name and the value, store the record.
		 */
		if (!conninfo_storeval(options, pname, pval, errorMessage, false, false))
		{
			PQconninfoFree(options);
			free(buf);
			return NULL;
		}
	}

	/* Done with the modifiable input string */
	free(buf);

	/*
	 * Add in defaults if the caller wants that.
	 */
	if (use_defaults)
	{
		if (!conninfo_add_defaults(options, errorMessage))
		{
			PQconninfoFree(options);
			return NULL;
		}
	}

	return options;
}