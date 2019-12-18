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
struct MPOpts {int /*<<< orphan*/  play_length; int /*<<< orphan*/  play_end; } ;
struct MPContext {struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double get_play_start_pts (struct MPContext*) ; 
 double rel_time_to_abs (struct MPContext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double get_play_end_pts_setting(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    double end = rel_time_to_abs(mpctx, opts->play_end);
    double length = rel_time_to_abs(mpctx, opts->play_length);
    if (length != MP_NOPTS_VALUE) {
        double start = get_play_start_pts(mpctx);
        if (end == MP_NOPTS_VALUE || start + length < end)
            end = start + length;
    }
    return end;
}