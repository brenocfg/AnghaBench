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

/* Variables and functions */
 int strlenW (char const*) ; 

__attribute__((used)) static const WCHAR* get_filename(const WCHAR* name, const WCHAR* endptr)
{
    const WCHAR*        ptr;

    if (!endptr) endptr = name + strlenW(name);
    for (ptr = endptr - 1; ptr >= name; ptr--)
    {
        if (*ptr == '/' || *ptr == '\\') break;
    }
    return ++ptr;
}