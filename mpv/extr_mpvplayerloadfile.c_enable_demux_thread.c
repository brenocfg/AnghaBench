#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct demuxer {int /*<<< orphan*/  fully_read; } ;
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_2__ {scalar_t__ demuxer_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  demux_set_wakeup_cb (struct demuxer*,int /*<<< orphan*/ ,struct MPContext*) ; 
 int /*<<< orphan*/  demux_start_thread (struct demuxer*) ; 
 int /*<<< orphan*/  wakeup_demux ; 

__attribute__((used)) static void enable_demux_thread(struct MPContext *mpctx, struct demuxer *demux)
{
    if (mpctx->opts->demuxer_thread && !demux->fully_read) {
        demux_set_wakeup_cb(demux, wakeup_demux, mpctx);
        demux_start_thread(demux);
    }
}