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
struct TYPE_3__ {scalar_t__ oprnamespace; int /*<<< orphan*/  oprname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__* Form_pg_operator ;

/* Variables and functions */
 char* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* get_namespace_name (scalar_t__) ; 
 int /*<<< orphan*/  quote_identifier (char const*) ; 

__attribute__((used)) static void
deparseOperatorName(StringInfo buf, Form_pg_operator opform)
{
	char	   *opname;

	/* opname is not a SQL identifier, so we should not quote it. */
	opname = NameStr(opform->oprname);

	/* Print schema name only if it's not pg_catalog */
	if (opform->oprnamespace != PG_CATALOG_NAMESPACE)
	{
		const char *opnspname;

		opnspname = get_namespace_name(opform->oprnamespace);
		/* Print fully qualified operator name. */
		appendStringInfo(buf, "OPERATOR(%s.%s)",
						 quote_identifier(opnspname), opname);
	}
	else
	{
		/* Just print operator name. */
		appendStringInfoString(buf, opname);
	}
}