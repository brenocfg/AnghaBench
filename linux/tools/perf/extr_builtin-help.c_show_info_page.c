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
 int /*<<< orphan*/  PERF_INFO_PATH ; 
 char* cmd_to_page (char const*) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_info_page(const char *perf_cmd)
{
	const char *page = cmd_to_page(perf_cmd);
	setenv("INFOPATH", system_path(PERF_INFO_PATH), 1);
	execlp("info", "info", "perfman", page, NULL);
	return -1;
}