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
typedef  int /*<<< orphan*/  RRD_ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE_NAME ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL_NAME ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL_NAME ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL_NAME ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

RRD_ALGORITHM rrd_algorithm_id(const char *name) {
    if(strcmp(name, RRD_ALGORITHM_INCREMENTAL_NAME) == 0)
        return RRD_ALGORITHM_INCREMENTAL;

    else if(strcmp(name, RRD_ALGORITHM_ABSOLUTE_NAME) == 0)
        return RRD_ALGORITHM_ABSOLUTE;

    else if(strcmp(name, RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL_NAME) == 0)
        return RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL;

    else if(strcmp(name, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL_NAME) == 0)
        return RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL;

    else
        return RRD_ALGORITHM_ABSOLUTE;
}