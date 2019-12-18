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
 int /*<<< orphan*/  conninfo_uri_parse_options (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PQconninfoOption *
conninfo_uri_parse(const char *uri, PQExpBuffer errorMessage,
				   bool use_defaults)
{
	PQconninfoOption *options;

	/* Make a working copy of PQconninfoOptions */
	options = conninfo_init(errorMessage);
	if (options == NULL)
		return NULL;

	if (!conninfo_uri_parse_options(options, uri, errorMessage))
	{
		PQconninfoFree(options);
		return NULL;
	}

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