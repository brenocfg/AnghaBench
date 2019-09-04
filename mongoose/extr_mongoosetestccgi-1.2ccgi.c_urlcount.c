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
 scalar_t__ isalnum (char const) ; 
 scalar_t__ strchr (char const*,char const) ; 

__attribute__((used)) static int
urlcount(const char *p, const char *keep) {
    int k;
    for (k = 0; *p != 0; p++) {
        if (isalnum(*p) || *p == ' ' ||
            (keep != 0 && strchr(keep, *p) != 0))
        {
            k++;
        }
        else {
            k += 3;
        }
    }
    return k;
}