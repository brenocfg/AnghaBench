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
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static WCHAR* GetWideStringN(const char* strA, int chars, DWORD *len)
{
    if(strA)
    {
        WCHAR* strW;
        *len = MultiByteToWideChar(CP_ACP, 0, strA, chars, NULL, 0);

        strW = HeapAlloc(GetProcessHeap(), 0, *len * sizeof(WCHAR));
        CHECK_ENOUGH_MEMORY(strW);
        MultiByteToWideChar(CP_ACP, 0, strA, chars, strW, *len);
        return strW;
    }
    *len = 0;
    return NULL;
}