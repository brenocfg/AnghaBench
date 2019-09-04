#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demuxer {TYPE_1__* desc; int /*<<< orphan*/  stream; scalar_t__ fully_read; struct demux_internal* in; } ;
struct demux_internal {TYPE_2__* d_thread; struct demuxer* d_user; int /*<<< orphan*/  threading; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* control ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUXER_CTRL_REPLACE_STREAM ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_memory_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void demux_maybe_replace_stream(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(!in->threading && demuxer == in->d_user);

    if (demuxer->fully_read) {
        MP_VERBOSE(demuxer, "assuming demuxer read all data; closing stream\n");
        free_stream(demuxer->stream);
        demuxer->stream = open_memory_stream(NULL, 0); // dummy
        in->d_thread->stream = demuxer->stream;

        if (demuxer->desc->control)
            demuxer->desc->control(in->d_thread, DEMUXER_CTRL_REPLACE_STREAM, NULL);
    }
}