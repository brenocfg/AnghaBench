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

/* Variables and functions */
 char* adapter_from_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 scalar_t__ is_numeric_index (char const*) ; 

const char *
rawsock_win_name(const char *ifname)
{
    if (is_numeric_index(ifname)) {
        const char *new_adapter_name;

        new_adapter_name = adapter_from_index(atoi(ifname));
        if (new_adapter_name)
            return new_adapter_name;
    }

    return ifname;
}