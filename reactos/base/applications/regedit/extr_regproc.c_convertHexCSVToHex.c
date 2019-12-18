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
typedef  char WCHAR ;
typedef  int UINT ;
typedef  int DWORD ;
typedef  char BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENOUGH_MEMORY (char*) ; 
 char* GetMultiByteString (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getAppName () ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strtoulW (char*,char**,int) ; 

__attribute__((used)) static BYTE* convertHexCSVToHex(WCHAR *str, DWORD *size)
{
    WCHAR *s;
    BYTE *d, *data;

    /* The worst case is 1 digit + 1 comma per byte */
    *size=(lstrlenW(str)+1)/2;
    data=HeapAlloc(GetProcessHeap(), 0, *size);
    CHECK_ENOUGH_MEMORY(data);

    s = str;
    d = data;
    *size=0;
    while (*s != '\0') {
        UINT wc;
        WCHAR *end;

        wc = strtoulW(s,&end,16);
        if (end == s || wc > 0xff || (*end && *end != ',')) {
            char* strA = GetMultiByteString(s);
            fprintf(stderr,"%S: ERROR converting CSV hex stream. Invalid value at '%s'\n",
                    getAppName(), strA);
            HeapFree(GetProcessHeap(), 0, data);
            HeapFree(GetProcessHeap(), 0, strA);
            return NULL;
        }
        *d++ =(BYTE)wc;
        (*size)++;
        if (*end) end++;
        s = end;
    }

    return data;
}