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
typedef  int /*<<< orphan*/  Scan ;
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyPlanFields (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scanrelid ; 

__attribute__((used)) static void
CopyScanFields(const Scan *from, Scan *newnode)
{
	CopyPlanFields((const Plan *) from, (Plan *) newnode);

	COPY_SCALAR_FIELD(scanrelid);
}