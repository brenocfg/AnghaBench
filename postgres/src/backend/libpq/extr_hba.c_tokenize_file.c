#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rawline ;
struct TYPE_9__ {int line_num; char* err_msg; int /*<<< orphan*/  raw_line; struct TYPE_9__* fields; } ;
typedef  TYPE_1__ TokenizedLine ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ List ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int MAX_LINE ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errcontext (char*,int,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* lappend (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* next_field_expand (char const*,char**,int,char**) ; 
 scalar_t__ palloc (int) ; 
 char* psprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static MemoryContext
tokenize_file(const char *filename, FILE *file, List **tok_lines, int elevel)
{
	int			line_number = 1;
	MemoryContext linecxt;
	MemoryContext oldcxt;

	linecxt = AllocSetContextCreate(CurrentMemoryContext,
									"tokenize_file",
									ALLOCSET_SMALL_SIZES);
	oldcxt = MemoryContextSwitchTo(linecxt);

	*tok_lines = NIL;

	while (!feof(file) && !ferror(file))
	{
		char		rawline[MAX_LINE];
		char	   *lineptr;
		List	   *current_line = NIL;
		char	   *err_msg = NULL;

		if (!fgets(rawline, sizeof(rawline), file))
		{
			int			save_errno = errno;

			if (!ferror(file))
				break;			/* normal EOF */
			/* I/O error! */
			ereport(elevel,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m", filename)));
			err_msg = psprintf("could not read file \"%s\": %s",
							   filename, strerror(save_errno));
			rawline[0] = '\0';
		}
		if (strlen(rawline) == MAX_LINE - 1)
		{
			/* Line too long! */
			ereport(elevel,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("authentication file line too long"),
					 errcontext("line %d of configuration file \"%s\"",
								line_number, filename)));
			err_msg = "authentication file line too long";
		}

		/* Strip trailing linebreak from rawline */
		lineptr = rawline + strlen(rawline) - 1;
		while (lineptr >= rawline && (*lineptr == '\n' || *lineptr == '\r'))
			*lineptr-- = '\0';

		/* Parse fields */
		lineptr = rawline;
		while (*lineptr && err_msg == NULL)
		{
			List	   *current_field;

			current_field = next_field_expand(filename, &lineptr,
											  elevel, &err_msg);
			/* add field to line, unless we are at EOL or comment start */
			if (current_field != NIL)
				current_line = lappend(current_line, current_field);
		}

		/* Reached EOL; emit line to TokenizedLine list unless it's boring */
		if (current_line != NIL || err_msg != NULL)
		{
			TokenizedLine *tok_line;

			tok_line = (TokenizedLine *) palloc(sizeof(TokenizedLine));
			tok_line->fields = current_line;
			tok_line->line_num = line_number;
			tok_line->raw_line = pstrdup(rawline);
			tok_line->err_msg = err_msg;
			*tok_lines = lappend(*tok_lines, tok_line);
		}

		line_number++;
	}

	MemoryContextSwitchTo(oldcxt);

	return linecxt;
}