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
typedef  int /*<<< orphan*/  ms ;
struct TYPE_3__ {int dwLength; int ullTotalPhys; int ullAvailPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMemoryStatusEx (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void log_available_memory(void)
{
	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(ms);

	GlobalMemoryStatusEx(&ms);

#ifdef _WIN64
	const char *note = "";
#else
	const char *note = " (NOTE: 32bit programs cannot use more than 3gb)";
#endif

	blog(LOG_INFO, "Physical Memory: %luMB Total, %luMB Free%s",
	     (DWORD)(ms.ullTotalPhys / 1048576),
	     (DWORD)(ms.ullAvailPhys / 1048576), note);
}