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
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Hash ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hashkeys ; 
 int /*<<< orphan*/  rows_total ; 
 int /*<<< orphan*/  skewColumn ; 
 int /*<<< orphan*/  skewInherit ; 
 int /*<<< orphan*/  skewTable ; 

__attribute__((used)) static void
_outHash(StringInfo str, const Hash *node)
{
	WRITE_NODE_TYPE("HASH");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_NODE_FIELD(hashkeys);
	WRITE_OID_FIELD(skewTable);
	WRITE_INT_FIELD(skewColumn);
	WRITE_BOOL_FIELD(skewInherit);
	WRITE_FLOAT_FIELD(rows_total, "%.0f");
}