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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  ColumnDef ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CHAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collClause ; 
 int /*<<< orphan*/  collOid ; 
 int /*<<< orphan*/  colname ; 
 int /*<<< orphan*/  constraints ; 
 int /*<<< orphan*/  cooked_default ; 
 int /*<<< orphan*/  fdwoptions ; 
 int /*<<< orphan*/  generated ; 
 int /*<<< orphan*/  identity ; 
 int /*<<< orphan*/  identitySequence ; 
 int /*<<< orphan*/  inhcount ; 
 int /*<<< orphan*/  is_from_type ; 
 int /*<<< orphan*/  is_local ; 
 int /*<<< orphan*/  is_not_null ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  raw_default ; 
 int /*<<< orphan*/  storage ; 
 int /*<<< orphan*/  typeName ; 

__attribute__((used)) static void
_outColumnDef(StringInfo str, const ColumnDef *node)
{
	WRITE_NODE_TYPE("COLUMNDEF");

	WRITE_STRING_FIELD(colname);
	WRITE_NODE_FIELD(typeName);
	WRITE_INT_FIELD(inhcount);
	WRITE_BOOL_FIELD(is_local);
	WRITE_BOOL_FIELD(is_not_null);
	WRITE_BOOL_FIELD(is_from_type);
	WRITE_CHAR_FIELD(storage);
	WRITE_NODE_FIELD(raw_default);
	WRITE_NODE_FIELD(cooked_default);
	WRITE_CHAR_FIELD(identity);
	WRITE_NODE_FIELD(identitySequence);
	WRITE_CHAR_FIELD(generated);
	WRITE_NODE_FIELD(collClause);
	WRITE_OID_FIELD(collOid);
	WRITE_NODE_FIELD(constraints);
	WRITE_NODE_FIELD(fdwoptions);
	WRITE_LOCATION_FIELD(location);
}