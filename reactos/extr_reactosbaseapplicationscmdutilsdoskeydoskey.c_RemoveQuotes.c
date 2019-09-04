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
typedef  int* LPWSTR ;

/* Variables and functions */
 int wcslen (int*) ; 

__attribute__((used)) static LPWSTR RemoveQuotes(LPWSTR str)
{
    WCHAR *end;
    if (*str == L'"' && *(end = str + wcslen(str) - 1) == L'"')
    {
        str++;
        *end = L'\0';
    }
    return str;
}