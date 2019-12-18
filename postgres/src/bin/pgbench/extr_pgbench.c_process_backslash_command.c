#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyscan_t ;
struct TYPE_8__ {int argc; char** argv; scalar_t__ meta; void* first_line; int /*<<< orphan*/  expr; int /*<<< orphan*/  stats; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_2__ Command ;

/* Variables and functions */
 int MAX_ARGS ; 
 int /*<<< orphan*/  META_COMMAND ; 
 scalar_t__ META_ELIF ; 
 scalar_t__ META_ELSE ; 
 scalar_t__ META_ENDIF ; 
 scalar_t__ META_GSET ; 
 scalar_t__ META_IF ; 
 scalar_t__ META_SET ; 
 scalar_t__ META_SETSHELL ; 
 scalar_t__ META_SHELL ; 
 scalar_t__ META_SLEEP ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ expr_lex_one_word (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  expr_parse_result ; 
 int /*<<< orphan*/  expr_scanner_finish (int /*<<< orphan*/ ) ; 
 int expr_scanner_get_lineno (int /*<<< orphan*/ ,int) ; 
 void* expr_scanner_get_substring (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  expr_scanner_init (int /*<<< orphan*/ ,char const*,int,int,char*) ; 
 int expr_scanner_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ expr_yyparse (int /*<<< orphan*/ ) ; 
 scalar_t__ getMetaCommand (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  initSimpleStats (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ pg_malloc0 (int) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syntax_error (char const*,int,void*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static Command *
process_backslash_command(PsqlScanState sstate, const char *source)
{
	Command    *my_command;
	PQExpBufferData word_buf;
	int			word_offset;
	int			offsets[MAX_ARGS];	/* offsets of argument words */
	int			start_offset;
	int			lineno;
	int			j;

	initPQExpBuffer(&word_buf);

	/* Remember location of the backslash */
	start_offset = expr_scanner_offset(sstate) - 1;
	lineno = expr_scanner_get_lineno(sstate, start_offset);

	/* Collect first word of command */
	if (!expr_lex_one_word(sstate, &word_buf, &word_offset))
	{
		termPQExpBuffer(&word_buf);
		return NULL;
	}

	/* Allocate and initialize Command structure */
	my_command = (Command *) pg_malloc0(sizeof(Command));
	my_command->type = META_COMMAND;
	my_command->argc = 0;
	initSimpleStats(&my_command->stats);

	/* Save first word (command name) */
	j = 0;
	offsets[j] = word_offset;
	my_command->argv[j++] = pg_strdup(word_buf.data);
	my_command->argc++;

	/* ... and convert it to enum form */
	my_command->meta = getMetaCommand(my_command->argv[0]);

	if (my_command->meta == META_SET ||
		my_command->meta == META_IF ||
		my_command->meta == META_ELIF)
	{
		yyscan_t	yyscanner;

		/* For \set, collect var name */
		if (my_command->meta == META_SET)
		{
			if (!expr_lex_one_word(sstate, &word_buf, &word_offset))
				syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
							 "missing argument", NULL, -1);

			offsets[j] = word_offset;
			my_command->argv[j++] = pg_strdup(word_buf.data);
			my_command->argc++;
		}

		/* then for all parse the expression */
		yyscanner = expr_scanner_init(sstate, source, lineno, start_offset,
									  my_command->argv[0]);

		if (expr_yyparse(yyscanner) != 0)
		{
			/* dead code: exit done from syntax_error called by yyerror */
			exit(1);
		}

		my_command->expr = expr_parse_result;

		/* Save line, trimming any trailing newline */
		my_command->first_line =
			expr_scanner_get_substring(sstate,
									   start_offset,
									   expr_scanner_offset(sstate),
									   true);

		expr_scanner_finish(yyscanner);

		termPQExpBuffer(&word_buf);

		return my_command;
	}

	/* For all other commands, collect remaining words. */
	while (expr_lex_one_word(sstate, &word_buf, &word_offset))
	{
		/*
		 * my_command->argv[0] is the command itself, so the max number of
		 * arguments is one less than MAX_ARGS
		 */
		if (j >= MAX_ARGS)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "too many arguments", NULL, -1);

		offsets[j] = word_offset;
		my_command->argv[j++] = pg_strdup(word_buf.data);
		my_command->argc++;
	}

	/* Save line, trimming any trailing newline */
	my_command->first_line =
		expr_scanner_get_substring(sstate,
								   start_offset,
								   expr_scanner_offset(sstate),
								   true);

	if (my_command->meta == META_SLEEP)
	{
		if (my_command->argc < 2)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "missing argument", NULL, -1);

		if (my_command->argc > 3)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "too many arguments", NULL,
						 offsets[3] - start_offset);

		/*
		 * Split argument into number and unit to allow "sleep 1ms" etc. We
		 * don't have to terminate the number argument with null because it
		 * will be parsed with atoi, which ignores trailing non-digit
		 * characters.
		 */
		if (my_command->argc == 2 && my_command->argv[1][0] != ':')
		{
			char	   *c = my_command->argv[1];

			while (isdigit((unsigned char) *c))
				c++;
			if (*c)
			{
				my_command->argv[2] = c;
				offsets[2] = offsets[1] + (c - my_command->argv[1]);
				my_command->argc = 3;
			}
		}

		if (my_command->argc == 3)
		{
			if (pg_strcasecmp(my_command->argv[2], "us") != 0 &&
				pg_strcasecmp(my_command->argv[2], "ms") != 0 &&
				pg_strcasecmp(my_command->argv[2], "s") != 0)
				syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
							 "unrecognized time unit, must be us, ms or s",
							 my_command->argv[2], offsets[2] - start_offset);
		}
	}
	else if (my_command->meta == META_SETSHELL)
	{
		if (my_command->argc < 3)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "missing argument", NULL, -1);
	}
	else if (my_command->meta == META_SHELL)
	{
		if (my_command->argc < 2)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "missing command", NULL, -1);
	}
	else if (my_command->meta == META_ELSE || my_command->meta == META_ENDIF)
	{
		if (my_command->argc != 1)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "unexpected argument", NULL, -1);
	}
	else if (my_command->meta == META_GSET)
	{
		if (my_command->argc > 2)
			syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
						 "too many arguments", NULL, -1);
	}
	else
	{
		/* my_command->meta == META_NONE */
		syntax_error(source, lineno, my_command->first_line, my_command->argv[0],
					 "invalid command", NULL, -1);
	}

	termPQExpBuffer(&word_buf);

	return my_command;
}