#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/ * t; } ;
typedef  TYPE_1__ RRDR ;

/* Variables and functions */

__attribute__((used)) static inline long rrdr_line_init(RRDR *r, time_t t, long rrdr_line) {
    rrdr_line++;

    #ifdef NETDATA_INTERNAL_CHECKS

    if(unlikely(rrdr_line >= r->n))
        error("INTERNAL ERROR: requested to step above RRDR size for chart '%s'", r->st->name);

    if(unlikely(r->t[rrdr_line] != 0 && r->t[rrdr_line] != t))
        error("INTERNAL ERROR: overwriting the timestamp of RRDR line %zu from %zu to %zu, of chart '%s'", (size_t)rrdr_line, (size_t)r->t[rrdr_line], (size_t)t, r->st->name);

    #endif

    // save the time
    r->t[rrdr_line] = t;

    return rrdr_line;
}