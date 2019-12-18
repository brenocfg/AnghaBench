#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pdo_column_data {void* param_type; int /*<<< orphan*/  name; int /*<<< orphan*/  maxlen; int /*<<< orphan*/  precision; } ;
struct TYPE_9__ {struct pdo_column_data* columns; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_5__* sqlvar; } ;
struct TYPE_10__ {TYPE_2__* H; TYPE_1__ out_sqlda; } ;
typedef  TYPE_4__ pdo_firebird_stmt ;
struct TYPE_11__ {int relname_length; int aliasname_length; int sqltype; int /*<<< orphan*/  sqlscale; int /*<<< orphan*/  aliasname; int /*<<< orphan*/  relname; int /*<<< orphan*/  sqllen; } ;
typedef  TYPE_5__ XSQLVAR ;
struct TYPE_8__ {scalar_t__ fetch_table_names; } ;

/* Variables and functions */
 void* PDO_PARAM_BOOL ; 
 void* PDO_PARAM_INT ; 
 void* PDO_PARAM_STR ; 
#define  SQL_BOOLEAN 131 
#define  SQL_INT64 130 
#define  SQL_LONG 129 
#define  SQL_SHORT 128 
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int firebird_stmt_describe(pdo_stmt_t *stmt, int colno) /* {{{ */
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;
	struct pdo_column_data *col = &stmt->columns[colno];
	XSQLVAR *var = &S->out_sqlda.sqlvar[colno];
	int colname_len;
	char *cp;

	colname_len = (S->H->fetch_table_names && var->relname_length)
					? (var->aliasname_length + var->relname_length + 1)
					: (var->aliasname_length);
	col->precision = -var->sqlscale;
	col->maxlen = var->sqllen;
	col->name = zend_string_alloc(colname_len, 0);
	cp = ZSTR_VAL(col->name);
	if (colname_len > var->aliasname_length) {
		memmove(cp, var->relname, var->relname_length);
		cp += var->relname_length;
		*cp++ = '.';
	}
	memmove(cp, var->aliasname, var->aliasname_length);
	*(cp+var->aliasname_length) = '\0';

	if (var->sqlscale < 0) {
		col->param_type = PDO_PARAM_STR;
	} else {
		switch (var->sqltype & ~1) {
			case SQL_SHORT:
			case SQL_LONG:
#if SIZEOF_ZEND_LONG >= 8
			case SQL_INT64:
#endif
				col->param_type = PDO_PARAM_INT;
				break;
#ifdef SQL_BOOLEAN
			case SQL_BOOLEAN:
				col->param_type = PDO_PARAM_BOOL;
				break;
#endif
			default:
				col->param_type = PDO_PARAM_STR;
				break;
		}
	}

	return 1;
}