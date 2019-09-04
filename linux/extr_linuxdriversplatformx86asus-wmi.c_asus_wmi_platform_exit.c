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
struct asus_wmi {int /*<<< orphan*/  platform_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  asus_wmi_sysfs_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asus_wmi_platform_exit(struct asus_wmi *asus)
{
	asus_wmi_sysfs_exit(asus->platform_device);
}