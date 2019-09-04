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
typedef  int BACKEND_OPTIONS ;

/* Variables and functions */
 int BACKEND_OPTIONS_SOURCE_BITS ; 
 int BACKEND_SOURCE_DATA_AS_COLLECTED ; 
 int BACKEND_SOURCE_DATA_AVERAGE ; 
 int BACKEND_SOURCE_DATA_SUM ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

inline BACKEND_OPTIONS backend_parse_data_source(const char *source, BACKEND_OPTIONS backend_options) {
    if(!strcmp(source, "raw") || !strcmp(source, "as collected") || !strcmp(source, "as-collected") || !strcmp(source, "as_collected") || !strcmp(source, "ascollected")) {
        backend_options |= BACKEND_SOURCE_DATA_AS_COLLECTED;
        backend_options &= ~(BACKEND_OPTIONS_SOURCE_BITS ^ BACKEND_SOURCE_DATA_AS_COLLECTED);
    }
    else if(!strcmp(source, "average")) {
        backend_options |= BACKEND_SOURCE_DATA_AVERAGE;
        backend_options &= ~(BACKEND_OPTIONS_SOURCE_BITS ^ BACKEND_SOURCE_DATA_AVERAGE);
    }
    else if(!strcmp(source, "sum") || !strcmp(source, "volume")) {
        backend_options |= BACKEND_SOURCE_DATA_SUM;
        backend_options &= ~(BACKEND_OPTIONS_SOURCE_BITS ^ BACKEND_SOURCE_DATA_SUM);
    }
    else {
        error("BACKEND: invalid data source method '%s'.", source);
    }

    return backend_options;
}