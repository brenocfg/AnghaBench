#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pg_wchar ;
typedef  int /*<<< orphan*/  errstr ;
struct TYPE_8__ {int line_num; scalar_t__ fields; } ;
typedef  TYPE_1__ TokenizedLine ;
struct TYPE_10__ {int /*<<< orphan*/  string; } ;
struct TYPE_9__ {int linenumber; char* ident_user; int /*<<< orphan*/  re; void* pg_role; void* usermap; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ IdentLine ;
typedef  TYPE_3__ HbaToken ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  C_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_INVALID_REGULAR_EXPRESSION ; 
 int /*<<< orphan*/  IDENT_FIELD_ABSENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDENT_MULTI_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  REG_ADVANCED ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 int /*<<< orphan*/ * lfirst (int /*<<< orphan*/ *) ; 
 TYPE_3__* linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (scalar_t__) ; 
 int /*<<< orphan*/ * lnext (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int pg_mb2wchar_with_len (char*,int /*<<< orphan*/ *,int) ; 
 int pg_regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 void* pstrdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static IdentLine *
parse_ident_line(TokenizedLine *tok_line)
{
	int			line_num = tok_line->line_num;
	ListCell   *field;
	List	   *tokens;
	HbaToken   *token;
	IdentLine  *parsedline;

	Assert(tok_line->fields != NIL);
	field = list_head(tok_line->fields);

	parsedline = palloc0(sizeof(IdentLine));
	parsedline->linenumber = line_num;

	/* Get the map token (must exist) */
	tokens = lfirst(field);
	IDENT_MULTI_VALUE(tokens);
	token = linitial(tokens);
	parsedline->usermap = pstrdup(token->string);

	/* Get the ident user token */
	field = lnext(tok_line->fields, field);
	IDENT_FIELD_ABSENT(field);
	tokens = lfirst(field);
	IDENT_MULTI_VALUE(tokens);
	token = linitial(tokens);
	parsedline->ident_user = pstrdup(token->string);

	/* Get the PG rolename token */
	field = lnext(tok_line->fields, field);
	IDENT_FIELD_ABSENT(field);
	tokens = lfirst(field);
	IDENT_MULTI_VALUE(tokens);
	token = linitial(tokens);
	parsedline->pg_role = pstrdup(token->string);

	if (parsedline->ident_user[0] == '/')
	{
		/*
		 * When system username starts with a slash, treat it as a regular
		 * expression. Pre-compile it.
		 */
		int			r;
		pg_wchar   *wstr;
		int			wlen;

		wstr = palloc((strlen(parsedline->ident_user + 1) + 1) * sizeof(pg_wchar));
		wlen = pg_mb2wchar_with_len(parsedline->ident_user + 1,
									wstr, strlen(parsedline->ident_user + 1));

		r = pg_regcomp(&parsedline->re, wstr, wlen, REG_ADVANCED, C_COLLATION_OID);
		if (r)
		{
			char		errstr[100];

			pg_regerror(r, &parsedline->re, errstr, sizeof(errstr));
			ereport(LOG,
					(errcode(ERRCODE_INVALID_REGULAR_EXPRESSION),
					 errmsg("invalid regular expression \"%s\": %s",
							parsedline->ident_user + 1, errstr)));

			pfree(wstr);
			return NULL;
		}
		pfree(wstr);
	}

	return parsedline;
}