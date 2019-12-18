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
struct TYPE_6__ {char* val; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 TYPE_1__* conninfo_find (TYPE_1__*,char const*) ; 
 char* conninfo_uri_decode (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static PQconninfoOption *
conninfo_storeval(PQconninfoOption *connOptions,
				  const char *keyword, const char *value,
				  PQExpBuffer errorMessage, bool ignoreMissing,
				  bool uri_decode)
{
	PQconninfoOption *option;
	char	   *value_copy;

	/*
	 * For backwards compatibility, requiressl=1 gets translated to
	 * sslmode=require, and requiressl=0 gets translated to sslmode=prefer
	 * (which is the default for sslmode).
	 */
	if (strcmp(keyword, "requiressl") == 0)
	{
		keyword = "sslmode";
		if (value[0] == '1')
			value = "require";
		else
			value = "prefer";
	}

	option = conninfo_find(connOptions, keyword);
	if (option == NULL)
	{
		if (!ignoreMissing)
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("invalid connection option \"%s\"\n"),
							  keyword);
		return NULL;
	}

	if (uri_decode)
	{
		value_copy = conninfo_uri_decode(value, errorMessage);
		if (value_copy == NULL)
			/* conninfo_uri_decode already set an error message */
			return NULL;
	}
	else
	{
		value_copy = strdup(value);
		if (value_copy == NULL)
		{
			printfPQExpBuffer(errorMessage, libpq_gettext("out of memory\n"));
			return NULL;
		}
	}

	if (option->val)
		free(option->val);
	option->val = value_copy;

	return option;
}