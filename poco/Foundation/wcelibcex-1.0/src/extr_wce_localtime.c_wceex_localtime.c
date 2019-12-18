#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {scalar_t__ wMonth; } ;
struct TYPE_5__ {int Bias; int StandardBias; TYPE_1__ StandardDate; } ;
typedef  TYPE_2__ TIME_ZONE_INFORMATION ;

/* Variables and functions */
 int GetTimeZoneInformation (TYPE_2__*) ; 
 struct tm* __wceex_offtime (int /*<<< orphan*/  const*,long) ; 

struct tm * wceex_localtime(const time_t *timer)
{
    register struct tm *tmp;

    long tzoffset;
    TIME_ZONE_INFORMATION tzi;
    
    // Retrive timezone offset in seconds
    tzoffset = 0;
	if (GetTimeZoneInformation(&tzi) != 0xFFFFFFFF)
	{
		tzoffset += (tzi.Bias * 60);
		if (tzi.StandardDate.wMonth != 0)
        {
			tzoffset += (tzi.StandardBias * 60);
        }
	}
    
    tzoffset *= -1;
    tmp = __wceex_offtime(timer, tzoffset);

    return tmp;
}