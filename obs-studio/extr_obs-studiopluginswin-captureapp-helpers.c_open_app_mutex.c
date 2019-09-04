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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  WTSGetActiveConsoleSessionId () ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nt_open_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_format ; 

HANDLE open_app_mutex(const wchar_t *sid, const wchar_t *name)
{
	wchar_t path[MAX_PATH];
	DWORD session_id = WTSGetActiveConsoleSessionId();
	_snwprintf(path, MAX_PATH, path_format, session_id, sid, name);
	return nt_open_mutex(path);
}