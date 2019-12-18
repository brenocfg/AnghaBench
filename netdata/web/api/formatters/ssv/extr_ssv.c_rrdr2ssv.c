#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ calculated_number ;
struct TYPE_5__ {scalar_t__ min; scalar_t__ max; } ;
typedef  int RRDR_OPTIONS ;
typedef  TYPE_1__ RRDR ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int RRDR_OPTION_NULL2ZERO ; 
 int RRDR_OPTION_REVERSED ; 
 int /*<<< orphan*/  buffer_rrd_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ rrdr2value (TYPE_1__*,long,int,int*) ; 
 int rrdr_rows (TYPE_1__*) ; 

void rrdr2ssv(RRDR *r, BUFFER *wb, RRDR_OPTIONS options, const char *prefix, const char *separator, const char *suffix) {
    //info("RRD2SSV(): %s: BEGIN", r->st->id);
    long i;

    buffer_strcat(wb, prefix);
    long start = 0, end = rrdr_rows(r), step = 1;
    if(!(options & RRDR_OPTION_REVERSED)) {
        start = rrdr_rows(r) - 1;
        end = -1;
        step = -1;
    }

    // for each line in the array
    for(i = start; i != end ;i += step) {
        int all_values_are_null = 0;
        calculated_number v = rrdr2value(r, i, options, &all_values_are_null);

        if(likely(i != start)) {
            if(r->min > v) r->min = v;
            if(r->max < v) r->max = v;
        }
        else {
            r->min = v;
            r->max = v;
        }

        if(likely(i != start))
            buffer_strcat(wb, separator);

        if(all_values_are_null) {
            if(options & RRDR_OPTION_NULL2ZERO)
                buffer_strcat(wb, "0");
            else
                buffer_strcat(wb, "null");
        }
        else
            buffer_rrd_value(wb, v);
    }
    buffer_strcat(wb, suffix);
    //info("RRD2SSV(): %s: END", r->st->id);
}