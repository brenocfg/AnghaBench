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
struct demuxer {struct demux_internal* in; } ;
struct demux_internal {struct demuxer* d_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_dealloc (struct demux_internal*) ; 
 int /*<<< orphan*/  demux_shutdown (struct demux_internal*) ; 
 int /*<<< orphan*/  demux_stop_thread (struct demuxer*) ; 

void demux_free(struct demuxer *demuxer)
{
    if (!demuxer)
        return;
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    demux_stop_thread(demuxer);
    demux_shutdown(in);
    demux_dealloc(in);
}