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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static WCHAR *strdupW(const WCHAR* str)
{
    WCHAR *ret;
    DWORD size = (strlenW(str) + 1) * sizeof(WCHAR);

    ret = HeapAlloc(GetProcessHeap(), 0, size);
    if(ret)
        memcpy(ret, str, size);
    return ret;
}