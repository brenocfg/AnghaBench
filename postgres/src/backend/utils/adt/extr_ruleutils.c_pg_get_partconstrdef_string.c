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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/ * deparse_context_for (char*,int /*<<< orphan*/ ) ; 
 char* deparse_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * get_partition_qual_relid (int /*<<< orphan*/ ) ; 

char *
pg_get_partconstrdef_string(Oid partitionId, char *aliasname)
{
	Expr	   *constr_expr;
	List	   *context;

	constr_expr = get_partition_qual_relid(partitionId);
	context = deparse_context_for(aliasname, partitionId);

	return deparse_expression((Node *) constr_expr, context, true, false);
}