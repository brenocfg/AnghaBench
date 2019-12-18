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
typedef  char* LPCWSTR ;
typedef  size_t GROUPFORMAT ;

/* Variables and functions */
 size_t NT_Unicode ; 

LPCWSTR GroupFormatToFormatName(GROUPFORMAT Format)
{
    static const LPCWSTR FormatNames[] =
    {
        L"Windows 3.1",
        L"NT Ansi",
        L"NT Unicode"
    };

    if (Format > NT_Unicode)
        return NULL;
    else
        return FormatNames[Format];
}