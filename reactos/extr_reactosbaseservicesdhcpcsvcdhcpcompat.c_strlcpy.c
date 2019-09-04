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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

size_t strlcpy(char *d, const char *s, size_t bufsize)
{
        size_t len = strlen(s);
        size_t ret = len;
        if (bufsize > 0) {
                if (len >= bufsize)
                        len = bufsize-1;
                memcpy(d, s, len);
                d[len] = 0;
        }
        return ret;
}