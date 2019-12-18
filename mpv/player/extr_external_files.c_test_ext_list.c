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
 int /*<<< orphan*/  bstr0 (char const* const) ; 
 scalar_t__ bstrcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool test_ext_list(bstr ext, const char *const *list)
{
    for (int n = 0; list[n]; n++) {
        if (bstrcasecmp(bstr0(list[n]), ext) == 0)
            return true;
    }
    return false;
}