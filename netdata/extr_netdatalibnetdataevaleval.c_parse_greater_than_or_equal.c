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
 scalar_t__ isoperatorterm_symbol (char const) ; 

__attribute__((used)) static inline int parse_greater_than_or_equal(const char **string) {
    const char *s = *string;

    // >=
    if(s[0] == '>' && s[1] == '=' && isoperatorterm_symbol(s[2])) {
        *string = &s[2];
        return 1;
    }

    return 0;
}