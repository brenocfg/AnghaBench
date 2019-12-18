#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  CustomName; } ;
typedef  TYPE_1__ CustomScanMethods ;

/* Variables and functions */
 int /*<<< orphan*/  RegisterExtensibleNodeEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  custom_scan_methods ; 

void
RegisterCustomScanMethods(const CustomScanMethods *methods)
{
	RegisterExtensibleNodeEntry(&custom_scan_methods,
								"Custom Scan Methods",
								methods->CustomName,
								methods);
}