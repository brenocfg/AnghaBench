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
 int /*<<< orphan*/ * conninfo_parse (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * conninfo_uri_parse (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uri_prefix_length (char const*) ; 

__attribute__((used)) static PQconninfoOption *
parse_connection_string(const char *connstr, PQExpBuffer errorMessage,
						bool use_defaults)
{
	/* Parse as URI if connection string matches URI prefix */
	if (uri_prefix_length(connstr) != 0)
		return conninfo_uri_parse(connstr, errorMessage, use_defaults);

	/* Parse as default otherwise */
	return conninfo_parse(connstr, errorMessage, use_defaults);
}