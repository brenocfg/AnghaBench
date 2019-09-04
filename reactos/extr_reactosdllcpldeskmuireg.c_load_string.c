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
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int* LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int HIWORD (int) ; 
 scalar_t__ LOWORD (int) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (scalar_t__) ; 
 scalar_t__ RT_STRING ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int load_string(HINSTANCE hModule, UINT resId, LPWSTR pwszBuffer, INT cMaxChars)
{
    HGLOBAL hMemory;
    HRSRC hResource;
    WCHAR *pString;
    int idxString;

    /* Negative values have to be inverted. */
    if (HIWORD(resId) == 0xffff)
        resId = (UINT)(-((INT)resId));

    /* Load the resource into memory and get a pointer to it. */
    hResource = FindResourceW(hModule, MAKEINTRESOURCEW(LOWORD(resId >> 4) + 1), (LPWSTR)RT_STRING);
    if (!hResource) return 0;
    hMemory = LoadResource(hModule, hResource);
    if (!hMemory) return 0;
    pString = LockResource(hMemory);

    /* Strings are length-prefixed. Lowest nibble of resId is an index. */
    idxString = resId & 0xf;
    while (idxString--) pString += *pString + 1;

    /* If no buffer is given, return length of the string. */
    if (!pwszBuffer) return *pString;

    /* Else copy over the string, respecting the buffer size. */
    cMaxChars = (*pString < cMaxChars) ? *pString : (cMaxChars - 1);
    if (cMaxChars >= 0)
    {
        memcpy(pwszBuffer, pString+1, cMaxChars * sizeof(WCHAR));
        pwszBuffer[cMaxChars] = L'\0';
    }

    return cMaxChars;
}