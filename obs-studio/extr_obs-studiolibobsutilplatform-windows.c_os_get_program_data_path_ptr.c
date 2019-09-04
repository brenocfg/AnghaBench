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
 int /*<<< orphan*/  CSIDL_COMMON_APPDATA ; 
 char* os_get_path_ptr_internal (char const*,int /*<<< orphan*/ ) ; 

char *os_get_program_data_path_ptr(const char *name)
{
	return os_get_path_ptr_internal(name, CSIDL_COMMON_APPDATA);
}