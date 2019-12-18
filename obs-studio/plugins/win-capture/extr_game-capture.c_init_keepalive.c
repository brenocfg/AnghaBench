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
struct game_capture {int /*<<< orphan*/  keepalive_mutex; int /*<<< orphan*/  process_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateMutexW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  WINDOW_HOOK_KEEPALIVE ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool init_keepalive(struct game_capture *gc)
{
	wchar_t new_name[64];
	_snwprintf(new_name, 64, L"%s%lu", WINDOW_HOOK_KEEPALIVE,
		   gc->process_id);

	gc->keepalive_mutex = CreateMutexW(NULL, false, new_name);
	if (!gc->keepalive_mutex) {
		warn("Failed to create keepalive mutex: %lu", GetLastError());
		return false;
	}

	return true;
}