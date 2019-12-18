#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sversion; } ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static void
printACLColumn(PQExpBuffer buf, const char *colname)
{
	if (pset.sversion >= 80100)
		appendPQExpBuffer(buf,
						  "pg_catalog.array_to_string(%s, E'\\n') AS \"%s\"",
						  colname, gettext_noop("Access privileges"));
	else
		appendPQExpBuffer(buf,
						  "pg_catalog.array_to_string(%s, '\\n') AS \"%s\"",
						  colname, gettext_noop("Access privileges"));
}