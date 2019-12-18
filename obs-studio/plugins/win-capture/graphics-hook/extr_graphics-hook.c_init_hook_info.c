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
struct hook_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_MAP_ALL_ACCESS ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_hook_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_hook_info ; 
 int /*<<< orphan*/  global_hook_info ; 
 int /*<<< orphan*/  hlog (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool init_hook_info(void)
{
	filemap_hook_info = create_hook_info(GetCurrentProcessId());
	if (!filemap_hook_info) {
		hlog("Failed to create hook info file mapping: %lu",
		     GetLastError());
		return false;
	}

	global_hook_info = MapViewOfFile(filemap_hook_info, FILE_MAP_ALL_ACCESS,
					 0, 0, sizeof(struct hook_info));
	if (!global_hook_info) {
		hlog("Failed to map the hook info file mapping: %lu",
		     GetLastError());
		return false;
	}

	return true;
}