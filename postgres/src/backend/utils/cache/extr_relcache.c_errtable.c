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
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  PG_DIAG_SCHEMA_NAME ; 
 int /*<<< orphan*/  PG_DIAG_TABLE_NAME ; 
 int /*<<< orphan*/  RelationGetNamespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_generic_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 

int
errtable(Relation rel)
{
	err_generic_string(PG_DIAG_SCHEMA_NAME,
					   get_namespace_name(RelationGetNamespace(rel)));
	err_generic_string(PG_DIAG_TABLE_NAME, RelationGetRelationName(rel));

	return 0;					/* return value does not matter */
}