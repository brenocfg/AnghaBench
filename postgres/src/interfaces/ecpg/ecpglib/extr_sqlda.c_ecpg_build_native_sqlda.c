#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sqlvar_struct {int dummy; } ;
struct sqlda_struct {int sqld; int sqln; int sqldabc; TYPE_2__* sqlvar; int /*<<< orphan*/  sqldaid; } ;
typedef  enum COMPAT_MODE { ____Placeholder_COMPAT_MODE } COMPAT_MODE ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {TYPE_1__ sqlname; int /*<<< orphan*/  sqltype; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 char* PQfname (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PQftype (int /*<<< orphan*/ *,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 scalar_t__ ecpg_alloc (long,int) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,int) ; 
 int /*<<< orphan*/  memset (struct sqlda_struct*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlda_dynamic_type (int /*<<< orphan*/ ,int) ; 
 long sqlda_native_total_size (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

struct sqlda_struct *
ecpg_build_native_sqlda(int line, PGresult *res, int row, enum COMPAT_MODE compat)
{
	struct sqlda_struct *sqlda;
	long		size;
	int			i;

	size = sqlda_native_total_size(res, row, compat);
	sqlda = (struct sqlda_struct *) ecpg_alloc(size, line);
	if (!sqlda)
		return NULL;

	memset(sqlda, 0, size);

	sprintf(sqlda->sqldaid, "SQLDA  ");
	sqlda->sqld = sqlda->sqln = PQnfields(res);
	ecpg_log("ecpg_build_native_sqlda on line %d sqld = %d\n", line, sqlda->sqld);
	sqlda->sqldabc = sizeof(struct sqlda_struct) + (sqlda->sqld - 1) * sizeof(struct sqlvar_struct);

	for (i = 0; i < sqlda->sqld; i++)
	{
		char	   *fname;

		sqlda->sqlvar[i].sqltype = sqlda_dynamic_type(PQftype(res, i), compat);
		fname = PQfname(res, i);
		sqlda->sqlvar[i].sqlname.length = strlen(fname);
		strcpy(sqlda->sqlvar[i].sqlname.data, fname);
	}

	return sqlda;
}