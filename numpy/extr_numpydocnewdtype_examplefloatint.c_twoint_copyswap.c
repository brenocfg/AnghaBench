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
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void
twoint_copyswap(void *dst, void *src, int swap, void *arr)
{
    if (src != NULL) {
        memcpy(dst, src, sizeof(double));
    }

    if (swap) {
        register char *a, *b, c;
        a = (char *)dst;
        b = a + 7;
        c = *a; *a++ = *b; *b-- = c;
        c = *a; *a++ = *b; *b-- = c;
        c = *a; *a++ = *b; *b-- = c;
        c = *a; *a++ = *b; *b   = c;
    }
}