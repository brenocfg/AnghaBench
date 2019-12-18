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
struct TYPE_3__ {int Denominator; int Numerator; } ;
typedef  TYPE_1__ DISPLAYCONFIG_RATIONAL ;

/* Variables and functions */

__attribute__((used)) static bool is_valid_refresh_rate(DISPLAYCONFIG_RATIONAL rr)
{
    // DisplayConfig sometimes reports a rate of 1 when the rate is not known
    return rr.Denominator != 0 && rr.Numerator / rr.Denominator > 1;
}