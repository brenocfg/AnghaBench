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
typedef  int /*<<< orphan*/  Scan ;
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  scanrelid ; 

__attribute__((used)) static void
_outScanInfo(StringInfo str, const Scan *node)
{
	_outPlanInfo(str, (const Plan *) node);

	WRITE_UINT_FIELD(scanrelid);
}