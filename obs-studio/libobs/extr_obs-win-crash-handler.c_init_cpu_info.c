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
typedef  int /*<<< orphan*/  wchar_t ;
struct exception_handler_data {int /*<<< orphan*/  cpu_info; } ;
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ERROR ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  PROCESSOR_REG_KEY ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_from_wcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void init_cpu_info(struct exception_handler_data *data)
{
	HKEY key;
	LSTATUS status;

	status = RegOpenKeyW(HKEY_LOCAL_MACHINE, PROCESSOR_REG_KEY, &key);
	if (status == ERROR_SUCCESS) {
		wchar_t str[1024];
		DWORD size = 1024;

		status = RegQueryValueExW(key, L"ProcessorNameString", NULL,
					  NULL, (LPBYTE)str, &size);
		if (status == ERROR_SUCCESS)
			dstr_from_wcs(&data->cpu_info, str);
		else
			dstr_copy(&data->cpu_info, CPU_ERROR);
	} else {
		dstr_copy(&data->cpu_info, CPU_ERROR);
	}
}