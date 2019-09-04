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

const char *statsd_parse_skip_spaces(const char *s) {
    char c;

    for(c = *s; c && ( c == ' ' || c == '\t' || c == '\r' || c == '\n' ); c = *++s) ;

    return s;
}