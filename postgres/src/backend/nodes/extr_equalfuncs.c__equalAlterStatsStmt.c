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
typedef  int /*<<< orphan*/  AlterStatsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defnames ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  stxstattarget ; 

__attribute__((used)) static bool
_equalAlterStatsStmt(const AlterStatsStmt *a, const AlterStatsStmt *b)
{
	COMPARE_NODE_FIELD(defnames);
	COMPARE_SCALAR_FIELD(stxstattarget);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}