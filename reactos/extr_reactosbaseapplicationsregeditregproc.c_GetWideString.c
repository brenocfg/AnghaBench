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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 

WCHAR* GetWideString(const char* strA)
{
    if(strA)
    {
        WCHAR* strW;
        int len = MultiByteToWideChar(CP_ACP, 0, strA, -1, NULL, 0);

        strW = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
        CHECK_ENOUGH_MEMORY(strW);
        MultiByteToWideChar(CP_ACP, 0, strA, -1, strW, len);
        return strW;
    }
    return NULL;
}