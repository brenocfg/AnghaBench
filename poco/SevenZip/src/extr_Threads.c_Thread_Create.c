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
typedef  int /*<<< orphan*/  WRes ;
typedef  int /*<<< orphan*/  THREAD_FUNC_TYPE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CThread ;

/* Variables and functions */
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  HandleToWRes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

WRes Thread_Create(CThread *p, THREAD_FUNC_TYPE func, LPVOID param)
{
  unsigned threadId; /* Windows Me/98/95: threadId parameter may not be NULL in _beginthreadex/CreateThread functions */
  *p =
    #ifdef UNDER_CE
    CreateThread(0, 0, func, param, 0, &threadId);
    #else
    (HANDLE)_beginthreadex(NULL, 0, func, param, 0, &threadId);
    #endif
    /* maybe we must use errno here, but probably GetLastError() is also OK. */
  return HandleToWRes(*p);
}