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
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;

/* Variables and functions */
 int atoiW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strchrW (int /*<<< orphan*/  const*,char) ; 

void msi_parse_version_string(LPCWSTR verStr, PDWORD ms, PDWORD ls)
{
    const WCHAR *ptr;
    int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

    x1 = atoiW(verStr);
    ptr = strchrW(verStr, '.');
    if (ptr)
    {
        x2 = atoiW(ptr + 1);
        ptr = strchrW(ptr + 1, '.');
    }
    if (ptr)
    {
        x3 = atoiW(ptr + 1);
        ptr = strchrW(ptr + 1, '.');
    }
    if (ptr)
        x4 = atoiW(ptr + 1);
    /* FIXME: byte-order dependent? */
    *ms = x1 << 16 | x2;
    if (ls) *ls = x3 << 16 | x4;
}