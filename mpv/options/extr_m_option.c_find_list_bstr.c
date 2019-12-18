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
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ bstr_equals0 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int find_list_bstr(char **list, bstr item)
{
    for (int n = 0; list && list[n]; n++) {
        if (bstr_equals0(item, list[n]))
            return n;
    }
    return -1;
}