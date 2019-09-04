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
struct TYPE_3__ {int len; unsigned char* start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */

__attribute__((used)) static bool maybe_text(bstr d)
{
    for (int n = 0; n < d.len; n++) {
        unsigned char c = d.start[n];
        if (c < 32 && c != '\n' && c != '\r' && c != '\t')
            return false;
    }
    return true;
}