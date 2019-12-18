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
typedef  int /*<<< orphan*/  AlterTSConfigurationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfgname ; 
 int /*<<< orphan*/  dicts ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  override ; 
 int /*<<< orphan*/  replace ; 
 int /*<<< orphan*/  tokentype ; 

__attribute__((used)) static bool
_equalAlterTSConfigurationStmt(const AlterTSConfigurationStmt *a,
							   const AlterTSConfigurationStmt *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_NODE_FIELD(cfgname);
	COMPARE_NODE_FIELD(tokentype);
	COMPARE_NODE_FIELD(dicts);
	COMPARE_SCALAR_FIELD(override);
	COMPARE_SCALAR_FIELD(replace);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}