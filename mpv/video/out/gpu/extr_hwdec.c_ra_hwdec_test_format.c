#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {TYPE_1__* driver; } ;
struct TYPE_2__ {int* imgfmts; } ;

/* Variables and functions */

bool ra_hwdec_test_format(struct ra_hwdec *hwdec, int imgfmt)
{
    for (int n = 0; hwdec->driver->imgfmts[n]; n++) {
        if (hwdec->driver->imgfmts[n] == imgfmt)
            return true;
    }
    return false;
}