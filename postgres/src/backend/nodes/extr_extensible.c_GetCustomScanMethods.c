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
typedef  int /*<<< orphan*/  CustomScanMethods ;

/* Variables and functions */
 scalar_t__ GetExtensibleNodeEntry (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  custom_scan_methods ; 

const CustomScanMethods *
GetCustomScanMethods(const char *CustomName, bool missing_ok)
{
	return (const CustomScanMethods *)
		GetExtensibleNodeEntry(custom_scan_methods,
							   CustomName,
							   missing_ok);
}