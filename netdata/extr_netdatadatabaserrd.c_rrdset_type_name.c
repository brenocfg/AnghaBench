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
typedef  int RRDSET_TYPE ;

/* Variables and functions */
#define  RRDSET_TYPE_AREA 130 
 char const* RRDSET_TYPE_AREA_NAME ; 
#define  RRDSET_TYPE_LINE 129 
 char const* RRDSET_TYPE_LINE_NAME ; 
#define  RRDSET_TYPE_STACKED 128 
 char const* RRDSET_TYPE_STACKED_NAME ; 

const char *rrdset_type_name(RRDSET_TYPE chart_type) {
    switch(chart_type) {
        case RRDSET_TYPE_LINE:
        default:
            return RRDSET_TYPE_LINE_NAME;

        case RRDSET_TYPE_AREA:
            return RRDSET_TYPE_AREA_NAME;

        case RRDSET_TYPE_STACKED:
            return RRDSET_TYPE_STACKED_NAME;
    }
}