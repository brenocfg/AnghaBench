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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ProcessHeap ; 

int LoadStringAndOem(HINSTANCE hInst,
                     UINT uID,
                     LPTSTR szNode,
                     int byteSize)
{
    TCHAR *szTmp;
    int res;

    szTmp = (LPTSTR)HeapAlloc(ProcessHeap, 0, byteSize);
    if (szTmp == NULL)
    {
        return 0;
    }

    res = LoadString(hInst, uID, szTmp, byteSize); 
    CharToOem(szTmp, szNode);
    HeapFree(ProcessHeap, 0, szTmp);
    return res;
}