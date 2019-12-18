#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_context ;
struct TYPE_6__ {int num_new_cols; char** new_colnames; int /*<<< orphan*/  printaliases; } ;
typedef  TYPE_2__ deparse_columns ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* quote_identifier (char*) ; 

__attribute__((used)) static void
get_column_alias_list(deparse_columns *colinfo, deparse_context *context)
{
	StringInfo	buf = context->buf;
	int			i;
	bool		first = true;

	/* Don't print aliases if not needed */
	if (!colinfo->printaliases)
		return;

	for (i = 0; i < colinfo->num_new_cols; i++)
	{
		char	   *colname = colinfo->new_colnames[i];

		if (first)
		{
			appendStringInfoChar(buf, '(');
			first = false;
		}
		else
			appendStringInfoString(buf, ", ");
		appendStringInfoString(buf, quote_identifier(colname));
	}
	if (!first)
		appendStringInfoChar(buf, ')');
}