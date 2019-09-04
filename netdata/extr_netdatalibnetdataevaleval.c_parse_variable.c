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
 int /*<<< orphan*/  isvariableterm (char const) ; 

__attribute__((used)) static inline int parse_variable(const char **string, char *buffer, size_t len) {
    const char *s = *string;

    // $
    if(*s == '$') {
        size_t i = 0;
        s++;

        if(*s == '{') {
            // ${variable_name}

            s++;
            while (*s && *s != '}' && i < len)
                buffer[i++] = *s++;

            if(*s == '}')
                s++;
        }
        else {
            // $variable_name

            while (*s && !isvariableterm(*s) && i < len)
                buffer[i++] = *s++;
        }

        buffer[i] = '\0';

        if (buffer[0]) {
            *string = s;
            return 1;
        }
    }

    return 0;
}