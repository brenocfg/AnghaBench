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
typedef  int /*<<< orphan*/  DefineStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  definition ; 
 int /*<<< orphan*/  defnames ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  oldstyle ; 
 int /*<<< orphan*/  replace ; 

__attribute__((used)) static bool
_equalDefineStmt(const DefineStmt *a, const DefineStmt *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_SCALAR_FIELD(oldstyle);
	COMPARE_NODE_FIELD(defnames);
	COMPARE_NODE_FIELD(args);
	COMPARE_NODE_FIELD(definition);
	COMPARE_SCALAR_FIELD(if_not_exists);
	COMPARE_SCALAR_FIELD(replace);

	return true;
}