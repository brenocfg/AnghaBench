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
struct demuxer {TYPE_2__* stream; int /*<<< orphan*/  cancel; int /*<<< orphan*/  global; struct demux_internal* in; } ;
struct demux_internal {TYPE_1__* d_user; int /*<<< orphan*/  owns_stream; struct demuxer* d_thread; int /*<<< orphan*/  threading; } ;
struct TYPE_5__ {int /*<<< orphan*/  cancel; } ;
struct TYPE_4__ {TYPE_2__* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_stream (TYPE_2__*) ; 
 TYPE_2__* stream_memory_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void demux_close_stream(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(!in->threading && demuxer == in->d_thread);

    if (!demuxer->stream || !in->owns_stream)
        return;

    MP_VERBOSE(demuxer, "demuxer read all data; closing stream\n");
    free_stream(demuxer->stream);
    demuxer->stream = stream_memory_open(demuxer->global, NULL, 0); // dummy
    demuxer->stream->cancel = demuxer->cancel;
    in->d_user->stream = demuxer->stream;
}