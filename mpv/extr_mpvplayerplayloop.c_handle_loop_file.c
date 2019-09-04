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
struct MPOpts {double* ab_loop; scalar_t__ loop_file; } ;
struct MPContext {scalar_t__ stop_play; struct MPOpts* opts; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 void* KEEP_PLAYING ; 
 int /*<<< orphan*/  MPSEEK_ABSOLUTE ; 
 int /*<<< orphan*/  MPSEEK_DEFAULT ; 
 int /*<<< orphan*/  MPSEEK_EXACT ; 
 int /*<<< orphan*/  MPSEEK_FLAG_NOFLUSH ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  OSD_FFW ; 
 double get_ab_loop_start_time (struct MPContext*) ; 
 int /*<<< orphan*/  mark_seek (struct MPContext*) ; 
 int /*<<< orphan*/  queue_seek (struct MPContext*,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_osd_function (struct MPContext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_loop_file(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;

    if (mpctx->stop_play == AT_END_OF_FILE &&
        (opts->ab_loop[0] != MP_NOPTS_VALUE || opts->ab_loop[1] != MP_NOPTS_VALUE))
    {
        // Assumes execute_queued_seek() happens before next audio/video is
        // attempted to be decoded or filtered.
        mpctx->stop_play = KEEP_PLAYING;
        double start = get_ab_loop_start_time(mpctx);
        if (start == MP_NOPTS_VALUE)
            start = 0;
        mark_seek(mpctx);
        queue_seek(mpctx, MPSEEK_ABSOLUTE, start, MPSEEK_EXACT,
                   MPSEEK_FLAG_NOFLUSH);
    }

    // Do not attempt to loop-file if --ab-loop is active.
    else if (opts->loop_file && mpctx->stop_play == AT_END_OF_FILE) {
        mpctx->stop_play = KEEP_PLAYING;
        set_osd_function(mpctx, OSD_FFW);
        queue_seek(mpctx, MPSEEK_ABSOLUTE, 0, MPSEEK_DEFAULT, MPSEEK_FLAG_NOFLUSH);
        if (opts->loop_file > 0)
            opts->loop_file--;
    }
}