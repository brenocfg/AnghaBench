#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  plan; } ;
typedef  TYPE_1__ Scan ;

/* Variables and functions */
 int /*<<< orphan*/  READ_TEMP_LOCALS () ; 
 int /*<<< orphan*/  READ_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadCommonPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scanrelid ; 

__attribute__((used)) static void
ReadCommonScan(Scan *local_node)
{
	READ_TEMP_LOCALS();

	ReadCommonPlan(&local_node->plan);

	READ_UINT_FIELD(scanrelid);
}