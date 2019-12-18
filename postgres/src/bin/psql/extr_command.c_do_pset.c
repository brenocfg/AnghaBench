#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct fmt   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int separator_zero; int /*<<< orphan*/ * separator; } ;
struct TYPE_8__ {int separator_zero; int /*<<< orphan*/ * separator; } ;
struct TYPE_11__ {int format; int expanded; char* csvFieldSep; int numericLocale; int tuples_only; int pager; int default_footer; void* columns; void* pager_min_lines; int /*<<< orphan*/ * tableAttr; TYPE_2__ recordSep; TYPE_1__ fieldSep; void* border; int /*<<< orphan*/  unicode_header_linestyle; int /*<<< orphan*/  unicode_column_linestyle; int /*<<< orphan*/  unicode_border_linestyle; int /*<<< orphan*/ * line_style; } ;
struct TYPE_10__ {TYPE_4__ topt; int /*<<< orphan*/ * title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_3__ printQueryOpt ;
typedef  enum printFormat { ____Placeholder_printFormat } printFormat ;
struct fmt {char const* name; int number; } ;
struct TYPE_12__ {int /*<<< orphan*/  popt; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  PRINT_ALIGNED 135 
#define  PRINT_ASCIIDOC 134 
#define  PRINT_CSV 133 
#define  PRINT_HTML 132 
#define  PRINT_LATEX 131 
 int PRINT_LATEX_LONGTABLE ; 
#define  PRINT_TROFF_MS 130 
#define  PRINT_UNALIGNED 129 
#define  PRINT_WRAPPED 128 
 int ParseVariableBool (char const*,char const*,int*) ; 
 int /*<<< orphan*/  PsqlVarEnumError (char const*,char const*,char*) ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int lengthof (TYPE_6__ const*) ; 
 int /*<<< orphan*/  pg_asciiformat ; 
 int /*<<< orphan*/  pg_asciiformat_old ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 void* pg_strdup (char const*) ; 
 scalar_t__ pg_strncasecmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  pg_utf8format ; 
 int /*<<< orphan*/  printPsetInfo (char const*,int /*<<< orphan*/ *) ; 
 TYPE_5__ pset ; 
 int /*<<< orphan*/  refresh_utf8format (TYPE_4__*) ; 
 scalar_t__ set_unicode_line_style (char const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

bool
do_pset(const char *param, const char *value, printQueryOpt *popt, bool quiet)
{
	size_t		vallen = 0;

	Assert(param != NULL);

	if (value)
		vallen = strlen(value);

	/* set format */
	if (strcmp(param, "format") == 0)
	{
		static const struct fmt
		{
			const char *name;
			enum printFormat number;
		}			formats[] =
		{
			/* remember to update error message below when adding more */
			{"aligned", PRINT_ALIGNED},
			{"asciidoc", PRINT_ASCIIDOC},
			{"csv", PRINT_CSV},
			{"html", PRINT_HTML},
			{"latex", PRINT_LATEX},
			{"troff-ms", PRINT_TROFF_MS},
			{"unaligned", PRINT_UNALIGNED},
			{"wrapped", PRINT_WRAPPED}
		};

		if (!value)
			;
		else
		{
			int			match_pos = -1;

			for (int i = 0; i < lengthof(formats); i++)
			{
				if (pg_strncasecmp(formats[i].name, value, vallen) == 0)
				{
					if (match_pos < 0)
						match_pos = i;
					else
					{
						pg_log_error("\\pset: ambiguous abbreviation \"%s\" matches both \"%s\" and \"%s\"",
									 value,
									 formats[match_pos].name, formats[i].name);
						return false;
					}
				}
			}
			if (match_pos >= 0)
				popt->topt.format = formats[match_pos].number;
			else if (pg_strncasecmp("latex-longtable", value, vallen) == 0)
			{
				/*
				 * We must treat latex-longtable specially because latex is a
				 * prefix of it; if both were in the table above, we'd think
				 * "latex" is ambiguous.
				 */
				popt->topt.format = PRINT_LATEX_LONGTABLE;
			}
			else
			{
				pg_log_error("\\pset: allowed formats are aligned, asciidoc, csv, html, latex, latex-longtable, troff-ms, unaligned, wrapped");
				return false;
			}
		}
	}

	/* set table line style */
	else if (strcmp(param, "linestyle") == 0)
	{
		if (!value)
			;
		else if (pg_strncasecmp("ascii", value, vallen) == 0)
			popt->topt.line_style = &pg_asciiformat;
		else if (pg_strncasecmp("old-ascii", value, vallen) == 0)
			popt->topt.line_style = &pg_asciiformat_old;
		else if (pg_strncasecmp("unicode", value, vallen) == 0)
			popt->topt.line_style = &pg_utf8format;
		else
		{
			pg_log_error("\\pset: allowed line styles are ascii, old-ascii, unicode");
			return false;
		}
	}

	/* set unicode border line style */
	else if (strcmp(param, "unicode_border_linestyle") == 0)
	{
		if (!value)
			;
		else if (set_unicode_line_style(value, vallen,
										&popt->topt.unicode_border_linestyle))
			refresh_utf8format(&(popt->topt));
		else
		{
			pg_log_error("\\pset: allowed Unicode border line styles are single, double");
			return false;
		}
	}

	/* set unicode column line style */
	else if (strcmp(param, "unicode_column_linestyle") == 0)
	{
		if (!value)
			;
		else if (set_unicode_line_style(value, vallen,
										&popt->topt.unicode_column_linestyle))
			refresh_utf8format(&(popt->topt));
		else
		{
			pg_log_error("\\pset: allowed Unicode column line styles are single, double");
			return false;
		}
	}

	/* set unicode header line style */
	else if (strcmp(param, "unicode_header_linestyle") == 0)
	{
		if (!value)
			;
		else if (set_unicode_line_style(value, vallen,
										&popt->topt.unicode_header_linestyle))
			refresh_utf8format(&(popt->topt));
		else
		{
			pg_log_error("\\pset: allowed Unicode header line styles are single, double");
			return false;
		}
	}

	/* set border style/width */
	else if (strcmp(param, "border") == 0)
	{
		if (value)
			popt->topt.border = atoi(value);
	}

	/* set expanded/vertical mode */
	else if (strcmp(param, "x") == 0 ||
			 strcmp(param, "expanded") == 0 ||
			 strcmp(param, "vertical") == 0)
	{
		if (value && pg_strcasecmp(value, "auto") == 0)
			popt->topt.expanded = 2;
		else if (value)
		{
			bool		on_off;

			if (ParseVariableBool(value, NULL, &on_off))
				popt->topt.expanded = on_off ? 1 : 0;
			else
			{
				PsqlVarEnumError(param, value, "on, off, auto");
				return false;
			}
		}
		else
			popt->topt.expanded = !popt->topt.expanded;
	}

	/* field separator for CSV format */
	else if (strcmp(param, "csv_fieldsep") == 0)
	{
		if (value)
		{
			/* CSV separator has to be a one-byte character */
			if (strlen(value) != 1)
			{
				pg_log_error("\\pset: csv_fieldsep must be a single one-byte character");
				return false;
			}
			if (value[0] == '"' || value[0] == '\n' || value[0] == '\r')
			{
				pg_log_error("\\pset: csv_fieldsep cannot be a double quote, a newline, or a carriage return");
				return false;
			}
			popt->topt.csvFieldSep[0] = value[0];
		}
	}

	/* locale-aware numeric output */
	else if (strcmp(param, "numericlocale") == 0)
	{
		if (value)
			return ParseVariableBool(value, param, &popt->topt.numericLocale);
		else
			popt->topt.numericLocale = !popt->topt.numericLocale;
	}

	/* null display */
	else if (strcmp(param, "null") == 0)
	{
		if (value)
		{
			free(popt->nullPrint);
			popt->nullPrint = pg_strdup(value);
		}
	}

	/* field separator for unaligned text */
	else if (strcmp(param, "fieldsep") == 0)
	{
		if (value)
		{
			free(popt->topt.fieldSep.separator);
			popt->topt.fieldSep.separator = pg_strdup(value);
			popt->topt.fieldSep.separator_zero = false;
		}
	}

	else if (strcmp(param, "fieldsep_zero") == 0)
	{
		free(popt->topt.fieldSep.separator);
		popt->topt.fieldSep.separator = NULL;
		popt->topt.fieldSep.separator_zero = true;
	}

	/* record separator for unaligned text */
	else if (strcmp(param, "recordsep") == 0)
	{
		if (value)
		{
			free(popt->topt.recordSep.separator);
			popt->topt.recordSep.separator = pg_strdup(value);
			popt->topt.recordSep.separator_zero = false;
		}
	}

	else if (strcmp(param, "recordsep_zero") == 0)
	{
		free(popt->topt.recordSep.separator);
		popt->topt.recordSep.separator = NULL;
		popt->topt.recordSep.separator_zero = true;
	}

	/* toggle between full and tuples-only format */
	else if (strcmp(param, "t") == 0 || strcmp(param, "tuples_only") == 0)
	{
		if (value)
			return ParseVariableBool(value, param, &popt->topt.tuples_only);
		else
			popt->topt.tuples_only = !popt->topt.tuples_only;
	}

	/* set title override */
	else if (strcmp(param, "C") == 0 || strcmp(param, "title") == 0)
	{
		free(popt->title);
		if (!value)
			popt->title = NULL;
		else
			popt->title = pg_strdup(value);
	}

	/* set HTML table tag options */
	else if (strcmp(param, "T") == 0 || strcmp(param, "tableattr") == 0)
	{
		free(popt->topt.tableAttr);
		if (!value)
			popt->topt.tableAttr = NULL;
		else
			popt->topt.tableAttr = pg_strdup(value);
	}

	/* toggle use of pager */
	else if (strcmp(param, "pager") == 0)
	{
		if (value && pg_strcasecmp(value, "always") == 0)
			popt->topt.pager = 2;
		else if (value)
		{
			bool		on_off;

			if (!ParseVariableBool(value, NULL, &on_off))
			{
				PsqlVarEnumError(param, value, "on, off, always");
				return false;
			}
			popt->topt.pager = on_off ? 1 : 0;
		}
		else if (popt->topt.pager == 1)
			popt->topt.pager = 0;
		else
			popt->topt.pager = 1;
	}

	/* set minimum lines for pager use */
	else if (strcmp(param, "pager_min_lines") == 0)
	{
		if (value)
			popt->topt.pager_min_lines = atoi(value);
	}

	/* disable "(x rows)" footer */
	else if (strcmp(param, "footer") == 0)
	{
		if (value)
			return ParseVariableBool(value, param, &popt->topt.default_footer);
		else
			popt->topt.default_footer = !popt->topt.default_footer;
	}

	/* set border style/width */
	else if (strcmp(param, "columns") == 0)
	{
		if (value)
			popt->topt.columns = atoi(value);
	}
	else
	{
		pg_log_error("\\pset: unknown option: %s", param);
		return false;
	}

	if (!quiet)
		printPsetInfo(param, &pset.popt);

	return true;
}