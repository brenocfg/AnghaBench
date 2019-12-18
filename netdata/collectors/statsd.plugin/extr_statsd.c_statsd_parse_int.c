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
 int /*<<< orphan*/  error (char*,char*,char const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 long long str2ll (char const*,char**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline long long statsd_parse_int(const char *v, long long def) {
    long long value;

    if(likely(v && *v)) {
        char *e = NULL;
        value = str2ll(v, &e);
        if(unlikely(e && *e))
            error("STATSD: excess data '%s' after value '%s'", e, v);
    }
    else
        value = def;

    return value;
}