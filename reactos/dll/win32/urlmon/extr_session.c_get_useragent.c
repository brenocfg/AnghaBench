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
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ensure_useragent () ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_cs ; 
 int /*<<< orphan*/  user_agent ; 

LPWSTR get_useragent(void)
{
    LPWSTR ret;

    ensure_useragent();

    EnterCriticalSection(&session_cs);
    ret = heap_strdupW(user_agent);
    LeaveCriticalSection(&session_cs);

    return ret;
}