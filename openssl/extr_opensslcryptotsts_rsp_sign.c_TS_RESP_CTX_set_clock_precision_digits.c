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
struct TYPE_3__ {unsigned int clock_precision_digits; } ;
typedef  TYPE_1__ TS_RESP_CTX ;

/* Variables and functions */
 unsigned int TS_MAX_CLOCK_PRECISION_DIGITS ; 

int TS_RESP_CTX_set_clock_precision_digits(TS_RESP_CTX *ctx,
                                           unsigned precision)
{
    if (precision > TS_MAX_CLOCK_PRECISION_DIGITS)
        return 0;
    ctx->clock_precision_digits = precision;
    return 1;
}