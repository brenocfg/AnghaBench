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
typedef  long time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; int tm_wday; int tm_yday; size_t tm_mon; int tm_mday; scalar_t__ tm_isdst; scalar_t__ tm_year; } ;

/* Variables and functions */
 long DAYS_PER_WEEK ; 
 long EPOCH_WDAY ; 
 int EPOCH_YEAR ; 
 long const SECS_PER_DAY ; 
 long SECS_PER_HOUR ; 
 long SECS_PER_MIN ; 
 scalar_t__ TM_YEAR_BASE ; 
 int isleap (int) ; 
 int** mon_lengths ; 
 scalar_t__* year_lengths ; 

struct tm * __wceex_offtime(const time_t *timer, long tzoffset)
{
    register struct tm *tmp;
    register long		days;
    register long		rem;
    register int		y;
    register int		yleap;
    register int       *ip;
    static struct tm    tm;

    tmp = &tm;
    days = *timer / SECS_PER_DAY;
    rem = *timer % SECS_PER_DAY;
    rem += tzoffset;
    while (rem < 0)
    {
        rem += SECS_PER_DAY;
        --days;
    }
    
    while (rem >= SECS_PER_DAY)
    {
        rem -= SECS_PER_DAY;
        ++days;
    }
    tmp->tm_hour = (int) (rem / SECS_PER_HOUR);

    rem = rem % SECS_PER_HOUR;
    tmp->tm_min = (int) (rem / SECS_PER_MIN);
    tmp->tm_sec = (int) (rem % SECS_PER_MIN);
    tmp->tm_wday = (int) ((EPOCH_WDAY + days) % DAYS_PER_WEEK);
    
    if (tmp->tm_wday < 0)
        tmp->tm_wday += DAYS_PER_WEEK;
    
    y = EPOCH_YEAR;
    
    if (days >= 0)
    {
        for ( ; ; )
        {
            yleap = isleap(y);
            if (days < (long) year_lengths[yleap])
                break;

            ++y;
            days = days - (long) year_lengths[yleap];
        }
    }
    else
    {
        do
        {
            --y;
            yleap = isleap(y);
            days = days + (long) year_lengths[yleap];
        } while (days < 0);
    }

    tmp->tm_year = y - TM_YEAR_BASE;
    tmp->tm_yday = (int) days;
    ip = mon_lengths[yleap];

    for (tmp->tm_mon = 0; days >= (long) ip[tmp->tm_mon]; ++(tmp->tm_mon))
    {
        days = days - (long) ip[tmp->tm_mon];
    }

    tmp->tm_mday = (int) (days + 1);
    tmp->tm_isdst = 0;

    return tmp;
}