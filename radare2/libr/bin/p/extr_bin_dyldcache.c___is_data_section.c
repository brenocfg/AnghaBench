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

/* Variables and functions */
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static bool __is_data_section(const char *name) {
	if (strstr (name, "_cstring")) {
		return true;
	}
	if (strstr (name, "_os_log")) {
		return true;
	}
	if (strstr (name, "_objc_methname")) {
		return true;
	}
	if (strstr (name, "_objc_classname")) {
		return true;
	}
	if (strstr (name, "_objc_methtype")) {
		return true;
	}
	return false;
}