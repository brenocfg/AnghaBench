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
typedef  int RRD_ALGORITHM ;

/* Variables and functions */
#define  RRD_ALGORITHM_ABSOLUTE 131 
 char const* RRD_ALGORITHM_ABSOLUTE_NAME ; 
#define  RRD_ALGORITHM_INCREMENTAL 130 
 char const* RRD_ALGORITHM_INCREMENTAL_NAME ; 
#define  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL 129 
 char const* RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL_NAME ; 
#define  RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL 128 
 char const* RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL_NAME ; 

const char *rrd_algorithm_name(RRD_ALGORITHM algorithm) {
    switch(algorithm) {
        case RRD_ALGORITHM_ABSOLUTE:
        default:
            return RRD_ALGORITHM_ABSOLUTE_NAME;

        case RRD_ALGORITHM_INCREMENTAL:
            return RRD_ALGORITHM_INCREMENTAL_NAME;

        case RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL:
            return RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL_NAME;

        case RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL:
            return RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL_NAME;
    }
}