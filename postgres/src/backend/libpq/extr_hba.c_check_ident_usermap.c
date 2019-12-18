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
struct TYPE_5__ {scalar_t__ rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  char pg_wchar ;
typedef  int /*<<< orphan*/  errstr ;
struct TYPE_6__ {char* usermap; char* ident_user; char* pg_role; int /*<<< orphan*/  re; } ;
typedef  TYPE_2__ IdentLine ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_REGULAR_EXPRESSION ; 
 int /*<<< orphan*/  LOG ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* palloc (int) ; 
 char* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_mb2wchar_with_len (char const*,char*,int) ; 
 int /*<<< orphan*/  pg_regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int pg_regexec (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strcasecmp (char*,char const*) ; 
 char* pstrdup (char const*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
check_ident_usermap(IdentLine *identLine, const char *usermap_name,
					const char *pg_role, const char *ident_user,
					bool case_insensitive, bool *found_p, bool *error_p)
{
	*found_p = false;
	*error_p = false;

	if (strcmp(identLine->usermap, usermap_name) != 0)
		/* Line does not match the map name we're looking for, so just abort */
		return;

	/* Match? */
	if (identLine->ident_user[0] == '/')
	{
		/*
		 * When system username starts with a slash, treat it as a regular
		 * expression. In this case, we process the system username as a
		 * regular expression that returns exactly one match. This is replaced
		 * for \1 in the database username string, if present.
		 */
		int			r;
		regmatch_t	matches[2];
		pg_wchar   *wstr;
		int			wlen;
		char	   *ofs;
		char	   *regexp_pgrole;

		wstr = palloc((strlen(ident_user) + 1) * sizeof(pg_wchar));
		wlen = pg_mb2wchar_with_len(ident_user, wstr, strlen(ident_user));

		r = pg_regexec(&identLine->re, wstr, wlen, 0, NULL, 2, matches, 0);
		if (r)
		{
			char		errstr[100];

			if (r != REG_NOMATCH)
			{
				/* REG_NOMATCH is not an error, everything else is */
				pg_regerror(r, &identLine->re, errstr, sizeof(errstr));
				ereport(LOG,
						(errcode(ERRCODE_INVALID_REGULAR_EXPRESSION),
						 errmsg("regular expression match for \"%s\" failed: %s",
								identLine->ident_user + 1, errstr)));
				*error_p = true;
			}

			pfree(wstr);
			return;
		}
		pfree(wstr);

		if ((ofs = strstr(identLine->pg_role, "\\1")) != NULL)
		{
			int			offset;

			/* substitution of the first argument requested */
			if (matches[1].rm_so < 0)
			{
				ereport(LOG,
						(errcode(ERRCODE_INVALID_REGULAR_EXPRESSION),
						 errmsg("regular expression \"%s\" has no subexpressions as requested by backreference in \"%s\"",
								identLine->ident_user + 1, identLine->pg_role)));
				*error_p = true;
				return;
			}

			/*
			 * length: original length minus length of \1 plus length of match
			 * plus null terminator
			 */
			regexp_pgrole = palloc0(strlen(identLine->pg_role) - 2 + (matches[1].rm_eo - matches[1].rm_so) + 1);
			offset = ofs - identLine->pg_role;
			memcpy(regexp_pgrole, identLine->pg_role, offset);
			memcpy(regexp_pgrole + offset,
				   ident_user + matches[1].rm_so,
				   matches[1].rm_eo - matches[1].rm_so);
			strcat(regexp_pgrole, ofs + 2);
		}
		else
		{
			/* no substitution, so copy the match */
			regexp_pgrole = pstrdup(identLine->pg_role);
		}

		/*
		 * now check if the username actually matched what the user is trying
		 * to connect as
		 */
		if (case_insensitive)
		{
			if (pg_strcasecmp(regexp_pgrole, pg_role) == 0)
				*found_p = true;
		}
		else
		{
			if (strcmp(regexp_pgrole, pg_role) == 0)
				*found_p = true;
		}
		pfree(regexp_pgrole);

		return;
	}
	else
	{
		/* Not regular expression, so make complete match */
		if (case_insensitive)
		{
			if (pg_strcasecmp(identLine->pg_role, pg_role) == 0 &&
				pg_strcasecmp(identLine->ident_user, ident_user) == 0)
				*found_p = true;
		}
		else
		{
			if (strcmp(identLine->pg_role, pg_role) == 0 &&
				strcmp(identLine->ident_user, ident_user) == 0)
				*found_p = true;
		}
	}
	return;
}