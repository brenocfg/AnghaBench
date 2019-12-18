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
 scalar_t__ LIKELY (void*) ; 
 int /*<<< orphan*/  LWAN_NO_DISCARD (void*) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void fourty_two_and_free(void *str)
{
    if (LIKELY(str)) {
        char *s = str;
        while (*s)
            *s++ = 42;
        LWAN_NO_DISCARD(str);
        free(str);
    }
}