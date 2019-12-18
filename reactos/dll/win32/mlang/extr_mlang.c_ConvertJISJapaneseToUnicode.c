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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ConvertJIS2SJIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MultiByteToWideChar (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_an (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static UINT ConvertJISJapaneseToUnicode(LPCSTR input, DWORD count,
                                        LPWSTR output, DWORD out_count)
{
    CHAR *sjis_string;
    UINT rc = 0;
    sjis_string = HeapAlloc(GetProcessHeap(),0,count);
    rc = ConvertJIS2SJIS(input,count,sjis_string);
    if (rc)
    {
        TRACE("%s\n",debugstr_an(sjis_string,rc));
        if (output)
            rc = MultiByteToWideChar(932,0,sjis_string,rc,output,out_count);
        else
            rc = MultiByteToWideChar(932,0,sjis_string,rc,0,0);
    }
    HeapFree(GetProcessHeap(),0,sjis_string);
    return rc;

}