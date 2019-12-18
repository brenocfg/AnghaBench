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
struct TYPE_7__ {char const* keyword; char const* val; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  PQconninfoFree (TYPE_1__*) ; 
 int /*<<< orphan*/  conninfo_add_defaults (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* conninfo_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 TYPE_1__* parse_connection_string (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ recognized_connection_string (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static PQconninfoOption *
conninfo_array_parse(const char *const *keywords, const char *const *values,
					 PQExpBuffer errorMessage, bool use_defaults,
					 int expand_dbname)
{
	PQconninfoOption *options;
	PQconninfoOption *dbname_options = NULL;
	PQconninfoOption *option;
	int			i = 0;

	/*
	 * If expand_dbname is non-zero, check keyword "dbname" to see if val is
	 * actually a recognized connection string.
	 */
	while (expand_dbname && keywords[i])
	{
		const char *pname = keywords[i];
		const char *pvalue = values[i];

		/* first find "dbname" if any */
		if (strcmp(pname, "dbname") == 0 && pvalue)
		{
			/*
			 * If value is a connection string, parse it, but do not use
			 * defaults here -- those get picked up later. We only want to
			 * override for those parameters actually passed.
			 */
			if (recognized_connection_string(pvalue))
			{
				dbname_options = parse_connection_string(pvalue, errorMessage, false);
				if (dbname_options == NULL)
					return NULL;
			}
			break;
		}
		++i;
	}

	/* Make a working copy of PQconninfoOptions */
	options = conninfo_init(errorMessage);
	if (options == NULL)
	{
		PQconninfoFree(dbname_options);
		return NULL;
	}

	/* Parse the keywords/values arrays */
	i = 0;
	while (keywords[i])
	{
		const char *pname = keywords[i];
		const char *pvalue = values[i];

		if (pvalue != NULL && pvalue[0] != '\0')
		{
			/* Search for the param record */
			for (option = options; option->keyword != NULL; option++)
			{
				if (strcmp(option->keyword, pname) == 0)
					break;
			}

			/* Check for invalid connection option */
			if (option->keyword == NULL)
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("invalid connection option \"%s\"\n"),
								  pname);
				PQconninfoFree(options);
				PQconninfoFree(dbname_options);
				return NULL;
			}

			/*
			 * If we are on the first dbname parameter, and we have a parsed
			 * connection string, copy those parameters across, overriding any
			 * existing previous settings.
			 */
			if (strcmp(pname, "dbname") == 0 && dbname_options)
			{
				PQconninfoOption *str_option;

				for (str_option = dbname_options; str_option->keyword != NULL; str_option++)
				{
					if (str_option->val != NULL)
					{
						int			k;

						for (k = 0; options[k].keyword; k++)
						{
							if (strcmp(options[k].keyword, str_option->keyword) == 0)
							{
								if (options[k].val)
									free(options[k].val);
								options[k].val = strdup(str_option->val);
								if (!options[k].val)
								{
									printfPQExpBuffer(errorMessage,
													  libpq_gettext("out of memory\n"));
									PQconninfoFree(options);
									PQconninfoFree(dbname_options);
									return NULL;
								}
								break;
							}
						}
					}
				}

				/*
				 * Forget the parsed connection string, so that any subsequent
				 * dbname parameters will not be expanded.
				 */
				PQconninfoFree(dbname_options);
				dbname_options = NULL;
			}
			else
			{
				/*
				 * Store the value, overriding previous settings
				 */
				if (option->val)
					free(option->val);
				option->val = strdup(pvalue);
				if (!option->val)
				{
					printfPQExpBuffer(errorMessage,
									  libpq_gettext("out of memory\n"));
					PQconninfoFree(options);
					PQconninfoFree(dbname_options);
					return NULL;
				}
			}
		}
		++i;
	}
	PQconninfoFree(dbname_options);

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