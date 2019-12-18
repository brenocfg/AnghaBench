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
struct demux_stream {scalar_t__ back_need_recheck; } ;
struct demux_internal {int back_any_need_recheck; int num_streams; TYPE_1__** streams; } ;
struct TYPE_2__ {struct demux_stream* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_backward_restart_pos (struct demux_stream*) ; 

__attribute__((used)) static void check_backward_seek(struct demux_internal *in)
{
    in->back_any_need_recheck = false;

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;

        if (ds->back_need_recheck)
            find_backward_restart_pos(ds);
    }
}