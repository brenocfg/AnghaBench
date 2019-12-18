#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dispchar; int /*<<< orphan*/ * keyword; } ;
typedef  TYPE_1__ PQconninfoOption ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ ForeignServerRelationId ; 
 scalar_t__ UserMappingRelationId ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool
is_valid_dblink_option(const PQconninfoOption *options, const char *option,
					   Oid context)
{
	const PQconninfoOption *opt;

	/* Look up the option in libpq result */
	for (opt = options; opt->keyword; opt++)
	{
		if (strcmp(opt->keyword, option) == 0)
			break;
	}
	if (opt->keyword == NULL)
		return false;

	/* Disallow debug options (particularly "replication") */
	if (strchr(opt->dispchar, 'D'))
		return false;

	/* Disallow "client_encoding" */
	if (strcmp(opt->keyword, "client_encoding") == 0)
		return false;

	/*
	 * If the option is "user" or marked secure, it should be specified only
	 * in USER MAPPING.  Others should be specified only in SERVER.
	 */
	if (strcmp(opt->keyword, "user") == 0 || strchr(opt->dispchar, '*'))
	{
		if (context != UserMappingRelationId)
			return false;
	}
	else
	{
		if (context != ForeignServerRelationId)
			return false;
	}

	return true;
}