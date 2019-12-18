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
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_xalloc (int) ; 

__attribute__((used)) static WCHAR *GetWideStringN(const char *strA, int size, DWORD *len)
{
    if (strA)
    {
        WCHAR *strW;
        *len = MultiByteToWideChar(CP_ACP, 0, strA, size, NULL, 0);

        strW = heap_xalloc(*len * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, 0, strA, size, strW, *len);
        return strW;
    }
    *len = 0;
    return NULL;
}