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
struct TYPE_4__ {scalar_t__ version; } ;
typedef  TYPE_1__ RSysInfo ;

/* Variables and functions */
 int atoi (scalar_t__) ; 
 TYPE_1__* r_sys_info () ; 
 int /*<<< orphan*/  r_sys_info_free (TYPE_1__*) ; 
 char* strchr (scalar_t__,char) ; 

__attribute__((used)) static bool __is_windows_ten() {
	int major = 0;
	RSysInfo *info = r_sys_info ();
	if (info && info->version) {
		char *dot = strchr (info->version, '.');
		if (dot) {
			*dot = '\0';
			major = atoi (info->version);
		}
	}
	r_sys_info_free (info);
	return major == 10;
}