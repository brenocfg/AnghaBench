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
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 size_t GetModuleBaseNameA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  hlog (char*,...) ; 
 scalar_t__* process_name ; 

__attribute__((used)) static inline void log_current_process(void)
{
	DWORD len = GetModuleBaseNameA(GetCurrentProcess(), NULL, process_name,
				       MAX_PATH);
	if (len > 0) {
		process_name[len] = 0;
		hlog("Hooked to process: %s", process_name);
	}

	hlog("(half life scientist) everything..  seems to be in order");
}