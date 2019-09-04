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

__attribute__((used)) static inline const char *statsd_parse_skip_up_to(const char *s, char d1, char d2) {
    char c;

    for(c = *s; c && c != d1 && c != d2 && c != '\r' && c != '\n'; c = *++s) ;

    return s;
}