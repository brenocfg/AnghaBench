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
typedef  int u_long ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_3__ {scalar_t__ DaylightBias; scalar_t__ Bias; scalar_t__ StandardBias; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;

/* Variables and functions */
 int GetTimeZoneInformation (TYPE_1__*) ; 
#define  TIME_ZONE_ID_DAYLIGHT 130 
#define  TIME_ZONE_ID_STANDARD 129 
#define  TIME_ZONE_ID_UNKNOWN 128 

ngx_int_t
ngx_gettimezone(void)
{
    u_long                 n;
    TIME_ZONE_INFORMATION  tz;

    n = GetTimeZoneInformation(&tz);

    switch (n) {

    case TIME_ZONE_ID_UNKNOWN:
        return -tz.Bias;

    case TIME_ZONE_ID_STANDARD:
        return -(tz.Bias + tz.StandardBias);

    case TIME_ZONE_ID_DAYLIGHT:
        return -(tz.Bias + tz.DaylightBias);

    default: /* TIME_ZONE_ID_INVALID */
        return 0;
    }
}