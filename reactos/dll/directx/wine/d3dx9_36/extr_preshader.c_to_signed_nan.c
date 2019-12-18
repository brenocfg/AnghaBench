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
typedef  int /*<<< orphan*/  ULONG64 ;

/* Variables and functions */
 scalar_t__ isnan (double) ; 

__attribute__((used)) static double to_signed_nan(double v)
{
    static const union
    {
        ULONG64 ulong64_value;
        double double_value;
    }
    signed_nan =
    {
        0xfff8000000000000
    };

    return isnan(v) ? signed_nan.double_value : v;
}