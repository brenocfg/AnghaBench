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
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline const char *statsd_parse_field_trim(const char *start, char *end) {
    if(unlikely(!start)) {
        start = end;
        return start;
    }

    while(start <= end && (*start == ' ' || *start == '\t'))
        start++;

    *end = '\0';
    end--;
    while(end >= start && (*end == ' ' || *end == '\t'))
        *end-- = '\0';

    return start;
}