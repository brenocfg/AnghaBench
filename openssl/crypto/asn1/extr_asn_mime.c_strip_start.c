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
 int /*<<< orphan*/  ossl_isspace (char) ; 

__attribute__((used)) static char *strip_start(char *name)
{
    char *p, c;
    /* Look for first non white space or quote */
    for (p = name; (c = *p); p++) {
        if (c == '"') {
            /* Next char is start of string if non null */
            if (p[1])
                return p + 1;
            /* Else null string */
            return NULL;
        }
        if (!ossl_isspace(c))
            return p;
    }
    return NULL;
}