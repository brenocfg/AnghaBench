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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int vsnprintfz(char *dst, size_t n, const char *fmt, va_list args) {
    int size = vsnprintf(dst, n, fmt, args);

    if (unlikely((size_t) size > n)) {
        // truncated
        size = (int)n;
    }

    dst[size] = '\0';
    return size;
}