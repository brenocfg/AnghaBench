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
typedef  int /*<<< orphan*/  LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*,char const*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2ld (char const*,char**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LONG_DOUBLE statsd_parse_float(const char *v, LONG_DOUBLE def) {
    LONG_DOUBLE value;

    if(likely(v && *v)) {
        char *e = NULL;
        value = str2ld(v, &e);
        if(unlikely(e && *e))
            error("STATSD: excess data '%s' after value '%s'", e, v);
    }
    else
        value = def;

    return value;
}