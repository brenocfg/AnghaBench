#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sqld; TYPE_1__* sqlvar; } ;
typedef  TYPE_2__ sqlda_t ;
typedef  int /*<<< orphan*/  decimal ;
struct TYPE_4__ {int* sqlind; char* sqlname; int sqltype; char* sqldata; } ;

/* Variables and functions */
#define  SQLCHAR 131 
#define  SQLDECIMAL 130 
#define  SQLFLOAT 129 
#define  SQLINT 128 
 int /*<<< orphan*/  dectoasc (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_sqlda(sqlda_t *sqlda)
{
	int	i;

	if (sqlda == NULL)
	{
		printf("dump_sqlda called with NULL sqlda\n");
		return;
	}

	for (i = 0; i < sqlda->sqld; i++)
	{
		if (sqlda->sqlvar[i].sqlind && *(sqlda->sqlvar[i].sqlind) == -1)
			printf("name sqlda descriptor: '%s' value NULL'\n", sqlda->sqlvar[i].sqlname);
		else
		switch (sqlda->sqlvar[i].sqltype)
		{
		case SQLCHAR:
			printf("name sqlda descriptor: '%s' value '%s'\n", sqlda->sqlvar[i].sqlname, sqlda->sqlvar[i].sqldata);
			break;
		case SQLINT:
			printf("name sqlda descriptor: '%s' value %d\n", sqlda->sqlvar[i].sqlname, *(int *)sqlda->sqlvar[i].sqldata);
			break;
		case SQLFLOAT:
			printf("name sqlda descriptor: '%s' value %f\n", sqlda->sqlvar[i].sqlname, *(double *)sqlda->sqlvar[i].sqldata);
			break;
		case SQLDECIMAL:
			{
				char    val[64];
				dectoasc((decimal *)sqlda->sqlvar[i].sqldata, val, 64, -1);
				printf("name sqlda descriptor: '%s' value DECIMAL '%s'\n", sqlda->sqlvar[i].sqlname, val);
				break;
			}
		}
	}
}