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
struct TYPE_3__ {long t; char const* m; } ;
typedef  TYPE_1__ OCSP_TBLSTR ;

/* Variables and functions */

__attribute__((used)) static const char *do_table2string(long s, const OCSP_TBLSTR *ts, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++, ts++)
        if (ts->t == s)
            return ts->m;
    return "(UNKNOWN)";
}