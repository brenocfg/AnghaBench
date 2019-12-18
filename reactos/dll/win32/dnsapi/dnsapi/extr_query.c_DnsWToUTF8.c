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
typedef  int /*<<< orphan*/ * PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/ * RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PCHAR
DnsWToUTF8(const WCHAR *WideString)
{
    PCHAR AnsiString;
    int AnsiLen = WideCharToMultiByte(CP_UTF8,
                                      0,
                                      WideString,
                                      -1,
                                      NULL,
                                      0,
                                      NULL,
                                      0);
    if (AnsiLen == 0)
        return NULL;
    AnsiString = RtlAllocateHeap(RtlGetProcessHeap(), 0, AnsiLen);
    if (AnsiString == NULL)
    {
        return NULL;
    }
    WideCharToMultiByte(CP_UTF8,
                        0,
                        WideString,
                        -1,
                        AnsiString,
                        AnsiLen,
                        NULL,
                        0);

    return AnsiString;
}