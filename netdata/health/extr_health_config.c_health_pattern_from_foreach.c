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
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  dimension_remove_pipe_comma (char*) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/ * simple_pattern_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strdupz (char*) ; 

SIMPLE_PATTERN *health_pattern_from_foreach(char *s) {
    char *convert= strdupz(s);
    SIMPLE_PATTERN *val = NULL;
    if(convert) {
        dimension_remove_pipe_comma(convert);
        val = simple_pattern_create(convert, NULL, SIMPLE_PATTERN_EXACT);

        freez(convert);
    }

    return val;
}