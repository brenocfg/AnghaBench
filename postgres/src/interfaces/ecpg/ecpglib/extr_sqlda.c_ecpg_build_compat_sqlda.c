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
struct sqlvar_compat {char* sqlname; int /*<<< orphan*/  sqltypelen; int /*<<< orphan*/  sqlxid; int /*<<< orphan*/  sqltype; } ;
struct sqlda_compat {int sqld; long desc_occ; struct sqlvar_compat* sqlvar; } ;
typedef  enum COMPAT_MODE { ____Placeholder_COMPAT_MODE } COMPAT_MODE ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PQfsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PQftype (int /*<<< orphan*/ *,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 scalar_t__ ecpg_alloc (long,int) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,int) ; 
 int /*<<< orphan*/  memset (struct sqlda_compat*,int /*<<< orphan*/ ,long) ; 
 long sqlda_compat_total_size (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlda_dynamic_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

struct sqlda_compat *
ecpg_build_compat_sqlda(int line, PGresult *res, int row, enum COMPAT_MODE compat)
{
	struct sqlda_compat *sqlda;
	struct sqlvar_compat *sqlvar;
	char	   *fname;
	long		size;
	int			sqld;
	int			i;

	size = sqlda_compat_total_size(res, row, compat);
	sqlda = (struct sqlda_compat *) ecpg_alloc(size, line);
	if (!sqlda)
		return NULL;

	memset(sqlda, 0, size);
	sqlvar = (struct sqlvar_compat *) (sqlda + 1);
	sqld = PQnfields(res);
	fname = (char *) (sqlvar + sqld);

	sqlda->sqld = sqld;
	ecpg_log("ecpg_build_compat_sqlda on line %d sqld = %d\n", line, sqld);
	sqlda->desc_occ = size;		/* cheat here, keep the full allocated size */
	sqlda->sqlvar = sqlvar;

	for (i = 0; i < sqlda->sqld; i++)
	{
		sqlda->sqlvar[i].sqltype = sqlda_dynamic_type(PQftype(res, i), compat);
		strcpy(fname, PQfname(res, i));
		sqlda->sqlvar[i].sqlname = fname;
		fname += strlen(sqlda->sqlvar[i].sqlname) + 1;

		/*
		 * this is reserved for future use, so we leave it empty for the time
		 * being
		 */
		/* sqlda->sqlvar[i].sqlformat = (char *) (long) PQfformat(res, i); */
		sqlda->sqlvar[i].sqlxid = PQftype(res, i);
		sqlda->sqlvar[i].sqltypelen = PQfsize(res, i);
	}

	return sqlda;
}