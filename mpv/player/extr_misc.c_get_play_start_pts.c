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
struct MPOpts {int /*<<< orphan*/  play_start; } ;
struct MPContext {int /*<<< orphan*/  play_dir; struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double get_start_time (struct MPContext*,int /*<<< orphan*/ ) ; 
 double rel_time_to_abs (struct MPContext*,int /*<<< orphan*/ ) ; 

double get_play_start_pts(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    double res = rel_time_to_abs(mpctx, opts->play_start);
    if (res == MP_NOPTS_VALUE)
        res = get_start_time(mpctx, mpctx->play_dir);
    return res;
}