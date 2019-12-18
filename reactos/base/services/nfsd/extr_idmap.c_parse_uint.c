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
typedef  int ptrdiff_t ;
typedef  scalar_t__ UINT ;
typedef  char const* PCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ const ULONG_MAX ; 
 scalar_t__ errno ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strtoul (char const*,char const**,int) ; 

__attribute__((used)) static BOOL parse_uint(
    const char *str,
    UINT *id_out)
{
    PCHAR endp;
    const UINT id = strtoul(str, &endp, 10);

    /* must convert the whole string */
    if ((endp - str) < (ptrdiff_t)strlen(str))
        return FALSE;

    /* result must fit in 32 bits */
    if (id == ULONG_MAX && errno == ERANGE)
        return FALSE;

    *id_out = id;
    return TRUE;
}