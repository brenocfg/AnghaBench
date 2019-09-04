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
struct TYPE_3__ {int num; char const* name; } ;
typedef  TYPE_1__ ssl_trace_tbl ;

/* Variables and functions */

__attribute__((used)) static const char *do_ssl_trace_str(int val, const ssl_trace_tbl *tbl,
                                    size_t ntbl)
{
    size_t i;

    for (i = 0; i < ntbl; i++, tbl++) {
        if (tbl->num == val)
            return tbl->name;
    }
    return "UNKNOWN";
}