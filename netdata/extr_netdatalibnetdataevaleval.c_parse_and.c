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
 scalar_t__ isoperatorterm_word (char const) ; 

__attribute__((used)) static inline int parse_and(const char **string) {
    const char *s = *string;

    // AND
    if((s[0] == 'A' || s[0] == 'a') && (s[1] == 'N' || s[1] == 'n') && (s[2] == 'D' || s[2] == 'd') && isoperatorterm_word(s[3])) {
        *string = &s[4];
        return 1;
    }

    // &&
    if(s[0] == '&' && s[1] == '&' && isoperatorterm_symbol(s[2])) {
        *string = &s[2];
        return 1;
    }

    return 0;
}