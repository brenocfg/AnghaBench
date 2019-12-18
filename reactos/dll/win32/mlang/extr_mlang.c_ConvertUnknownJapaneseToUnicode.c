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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int CP_ACP ; 
 int /*<<< orphan*/  ConvertJIS2SJIS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DetectJapaneseCode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int debugstr_an (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ConvertUnknownJapaneseToUnicode(LPCSTR input, DWORD count,
                                            LPWSTR output, DWORD out_count)
{
    CHAR *sjis_string;
    UINT rc = 0;
    int code = DetectJapaneseCode(input,count);
    TRACE("Japanese code %i\n",code);

    switch (code)
    {
    case 0:
        if (output)
            rc = MultiByteToWideChar(CP_ACP,0,input,count,output,out_count);
        else
            rc = MultiByteToWideChar(CP_ACP,0,input,count,0,0);
        break;

    case 932:
        if (output)
            rc = MultiByteToWideChar(932,0,input,count,output,out_count);
        else
            rc = MultiByteToWideChar(932,0,input,count,0,0);
        break;

    case 51932:
        if (output)
            rc = MultiByteToWideChar(20932,0,input,count,output,out_count);
        else
            rc = MultiByteToWideChar(20932,0,input,count,0,0);
        break;

    case 50220:
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
        break;
    }
    return rc;
}