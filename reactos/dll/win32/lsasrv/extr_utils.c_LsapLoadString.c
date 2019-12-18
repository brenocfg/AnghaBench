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
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
typedef  scalar_t__* LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int LOWORD (int) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int) ; 
 scalar_t__ RT_STRING ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int min (int,scalar_t__) ; 

INT
LsapLoadString(HINSTANCE hInstance,
               UINT uId,
               LPWSTR lpBuffer,
               INT nBufferMax)
{
    HGLOBAL hmem;
    HRSRC hrsrc;
    WCHAR *p;
    int string_num;
    int i;

    /* Use loword (incremented by 1) as resourceid */
    hrsrc = FindResourceW(hInstance,
                          MAKEINTRESOURCEW((LOWORD(uId) >> 4) + 1),
                          (LPWSTR)RT_STRING);
    if (!hrsrc)
        return 0;

    hmem = LoadResource(hInstance, hrsrc);
    if (!hmem)
        return 0;

    p = LockResource(hmem);
    string_num = uId & 0x000f;
    for (i = 0; i < string_num; i++)
        p += *p + 1;

    i = min(nBufferMax - 1, *p);
    if (i > 0)
    {
        memcpy(lpBuffer, p + 1, i * sizeof(WCHAR));
        lpBuffer[i] = 0;
    }
    else
    {
        if (nBufferMax > 1)
        {
            lpBuffer[0] = 0;
            return 0;
        }
    }

    return i;
}