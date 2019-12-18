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
 scalar_t__ isspace (unsigned char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *strip_spaces(char *p)
{
    char *q;

    /* Skip over leading spaces */
    while (*p && isspace((unsigned char)*p))
        p++;
    if (*p == '\0')
        return NULL;

    for (q = p + strlen(p) - 1; q != p && isspace((unsigned char)*q); )
        *q-- = '\0';
    return *p ? p : NULL;
}