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
 char* _ (char*) ; 
 char* default_text_search_config ; 
 void* find_matching_ts_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc_ctype ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
setup_text_search(void)
{
	if (!default_text_search_config)
	{
		default_text_search_config = find_matching_ts_config(lc_ctype);
		if (!default_text_search_config)
		{
			pg_log_info("could not find suitable text search configuration for locale \"%s\"",
						lc_ctype);
			default_text_search_config = "simple";
		}
	}
	else
	{
		const char *checkmatch = find_matching_ts_config(lc_ctype);

		if (checkmatch == NULL)
		{
			pg_log_warning("suitable text search configuration for locale \"%s\" is unknown",
						   lc_ctype);
		}
		else if (strcmp(checkmatch, default_text_search_config) != 0)
		{
			pg_log_warning("specified text search configuration \"%s\" might not match locale \"%s\"",
						   default_text_search_config, lc_ctype);
		}
	}

	printf(_("The default text search configuration will be set to \"%s\".\n"),
		   default_text_search_config);

}