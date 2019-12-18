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

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
#define  T_Float 129 
#define  T_Integer 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intVal (int /*<<< orphan*/ *) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidin_subr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ *) ; 

Oid
oidparse(Node *node)
{
	switch (nodeTag(node))
	{
		case T_Integer:
			return intVal(node);
		case T_Float:

			/*
			 * Values too large for int4 will be represented as Float
			 * constants by the lexer.  Accept these if they are valid OID
			 * strings.
			 */
			return oidin_subr(strVal(node), NULL);
		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(node));
	}
	return InvalidOid;			/* keep compiler quiet */
}