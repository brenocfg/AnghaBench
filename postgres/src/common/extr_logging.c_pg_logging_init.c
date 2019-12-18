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

/* Variables and functions */
 int /*<<< orphan*/  PG_LOG_INFO ; 
 void* SGR_ERROR_DEFAULT ; 
 void* SGR_LOCUS_DEFAULT ; 
 void* SGR_WARNING_DEFAULT ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  __pg_log_level ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_progname (char const*) ; 
 char* getenv (char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sgr_error ; 
 void* sgr_locus ; 
 void* sgr_warning ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

void
pg_logging_init(const char *argv0)
{
	const char *pg_color_env = getenv("PG_COLOR");
	bool		log_color = false;

	/* usually the default, but not on Windows */
	setvbuf(stderr, NULL, _IONBF, 0);

	progname = get_progname(argv0);
	__pg_log_level = PG_LOG_INFO;

	if (pg_color_env)
	{
		if (strcmp(pg_color_env, "always") == 0 ||
			(strcmp(pg_color_env, "auto") == 0 && isatty(fileno(stderr))))
			log_color = true;
	}

	if (log_color)
	{
		const char *pg_colors_env = getenv("PG_COLORS");

		if (pg_colors_env)
		{
			char	   *colors = strdup(pg_colors_env);

			if (colors)
			{
				for (char *token = strtok(colors, ":"); token; token = strtok(NULL, ":"))
				{
					char	   *e = strchr(token, '=');

					if (e)
					{
						char	   *name;
						char	   *value;

						*e = '\0';
						name = token;
						value = e + 1;

						if (strcmp(name, "error") == 0)
							sgr_error = strdup(value);
						if (strcmp(name, "warning") == 0)
							sgr_warning = strdup(value);
						if (strcmp(name, "locus") == 0)
							sgr_locus = strdup(value);
					}
				}

				free(colors);
			}
		}
		else
		{
			sgr_error = SGR_ERROR_DEFAULT;
			sgr_warning = SGR_WARNING_DEFAULT;
			sgr_locus = SGR_LOCUS_DEFAULT;
		}
	}
}