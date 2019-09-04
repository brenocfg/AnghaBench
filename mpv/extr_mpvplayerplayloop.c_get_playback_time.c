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
struct MPContext {double playback_pts; } ;

/* Variables and functions */
 double MPCLAMP (double,int /*<<< orphan*/ ,double) ; 
 double MP_NOPTS_VALUE ; 
 double get_current_time (struct MPContext*) ; 
 double get_time_length (struct MPContext*) ; 

double get_playback_time(struct MPContext *mpctx)
{
    double cur = get_current_time(mpctx);
    if (cur == MP_NOPTS_VALUE)
        return cur;
    // During seeking, the time corresponds to the last seek time - apply some
    // cosmetics to it.
    if (mpctx->playback_pts == MP_NOPTS_VALUE) {
        double length = get_time_length(mpctx);
        if (length >= 0)
            cur = MPCLAMP(cur, 0, length);
    }
    return cur;
}