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
typedef  scalar_t__* PCHAR ;

/* Variables and functions */
 scalar_t__ isspace (scalar_t__) ; 

__attribute__((used)) static
PCHAR
IniCacheSkipWhitespace(
    PCHAR Ptr)
{
    while (*Ptr != 0 && isspace(*Ptr))
        Ptr++;

    return (*Ptr == 0) ? NULL : Ptr;
}