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
typedef  int /*<<< orphan*/  MPContext ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double get_playback_time (int /*<<< orphan*/ *) ; 
 double get_time_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool time_remaining(MPContext *mpctx, double *remaining)
{
    double len = get_time_length(mpctx);
    double playback = get_playback_time(mpctx);

    if (playback == MP_NOPTS_VALUE || len <= 0)
        return false;

    *remaining = len - playback;

    return len >= 0;
}