#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* separator; int separator_zero; } ;
struct TYPE_5__ {char* separator; int separator_zero; } ;
struct TYPE_8__ {char* csvFieldSep; int expanded; int default_footer; int numericLocale; char* tableAttr; int tuples_only; int /*<<< orphan*/  unicode_header_linestyle; int /*<<< orphan*/  unicode_column_linestyle; int /*<<< orphan*/  unicode_border_linestyle; TYPE_2__ recordSep; int /*<<< orphan*/  pager_min_lines; int /*<<< orphan*/  pager; int /*<<< orphan*/  format; TYPE_1__ fieldSep; int /*<<< orphan*/  columns; int /*<<< orphan*/  border; } ;
struct printQueryOpt {char* nullPrint; char* title; TYPE_4__ topt; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _align2string (int /*<<< orphan*/ ) ; 
 char* _unicode_linestyle2string (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_line_style (TYPE_4__*) ; 
 char* pset_bool_string (int) ; 
 char* pset_quoted_string (char*) ; 
 char* psprintf (char*,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static char *
pset_value_string(const char *param, struct printQueryOpt *popt)
{
	Assert(param != NULL);

	if (strcmp(param, "border") == 0)
		return psprintf("%d", popt->topt.border);
	else if (strcmp(param, "columns") == 0)
		return psprintf("%d", popt->topt.columns);
	else if (strcmp(param, "csv_fieldsep") == 0)
		return pset_quoted_string(popt->topt.csvFieldSep);
	else if (strcmp(param, "expanded") == 0)
		return pstrdup(popt->topt.expanded == 2
					   ? "auto"
					   : pset_bool_string(popt->topt.expanded));
	else if (strcmp(param, "fieldsep") == 0)
		return pset_quoted_string(popt->topt.fieldSep.separator
								  ? popt->topt.fieldSep.separator
								  : "");
	else if (strcmp(param, "fieldsep_zero") == 0)
		return pstrdup(pset_bool_string(popt->topt.fieldSep.separator_zero));
	else if (strcmp(param, "footer") == 0)
		return pstrdup(pset_bool_string(popt->topt.default_footer));
	else if (strcmp(param, "format") == 0)
		return psprintf("%s", _align2string(popt->topt.format));
	else if (strcmp(param, "linestyle") == 0)
		return psprintf("%s", get_line_style(&popt->topt)->name);
	else if (strcmp(param, "null") == 0)
		return pset_quoted_string(popt->nullPrint
								  ? popt->nullPrint
								  : "");
	else if (strcmp(param, "numericlocale") == 0)
		return pstrdup(pset_bool_string(popt->topt.numericLocale));
	else if (strcmp(param, "pager") == 0)
		return psprintf("%d", popt->topt.pager);
	else if (strcmp(param, "pager_min_lines") == 0)
		return psprintf("%d", popt->topt.pager_min_lines);
	else if (strcmp(param, "recordsep") == 0)
		return pset_quoted_string(popt->topt.recordSep.separator
								  ? popt->topt.recordSep.separator
								  : "");
	else if (strcmp(param, "recordsep_zero") == 0)
		return pstrdup(pset_bool_string(popt->topt.recordSep.separator_zero));
	else if (strcmp(param, "tableattr") == 0)
		return popt->topt.tableAttr ? pset_quoted_string(popt->topt.tableAttr) : pstrdup("");
	else if (strcmp(param, "title") == 0)
		return popt->title ? pset_quoted_string(popt->title) : pstrdup("");
	else if (strcmp(param, "tuples_only") == 0)
		return pstrdup(pset_bool_string(popt->topt.tuples_only));
	else if (strcmp(param, "unicode_border_linestyle") == 0)
		return pstrdup(_unicode_linestyle2string(popt->topt.unicode_border_linestyle));
	else if (strcmp(param, "unicode_column_linestyle") == 0)
		return pstrdup(_unicode_linestyle2string(popt->topt.unicode_column_linestyle));
	else if (strcmp(param, "unicode_header_linestyle") == 0)
		return pstrdup(_unicode_linestyle2string(popt->topt.unicode_header_linestyle));
	else
		return pstrdup("ERROR");
}