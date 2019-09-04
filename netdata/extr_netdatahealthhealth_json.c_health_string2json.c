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
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  buffer_strcat_htmlescape (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline void health_string2json(BUFFER *wb, const char *prefix, const char *label, const char *value, const char *suffix) {
    if(value && *value) {
        buffer_sprintf(wb, "%s\"%s\":\"", prefix, label);
        buffer_strcat_htmlescape(wb, value);
        buffer_strcat(wb, "\"");
        buffer_strcat(wb, suffix);
    }
    else
        buffer_sprintf(wb, "%s\"%s\":null%s", prefix, label, suffix);
}