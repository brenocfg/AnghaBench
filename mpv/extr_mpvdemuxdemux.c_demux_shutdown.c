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
struct demuxer {int /*<<< orphan*/ * stream; int /*<<< orphan*/ * priv; TYPE_1__* desc; } ;
struct demux_internal {scalar_t__ total_bytes; scalar_t__ owns_stream; TYPE_2__* d_thread; int /*<<< orphan*/ * recorder; struct demuxer* d_user; } ;
struct TYPE_4__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_flush (struct demuxer*) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_recorder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void demux_shutdown(struct demux_internal *in)
{
    struct demuxer *demuxer = in->d_user;

    if (in->recorder) {
        mp_recorder_destroy(in->recorder);
        in->recorder = NULL;
    }

    if (demuxer->desc->close)
        demuxer->desc->close(in->d_thread);
    demuxer->priv = NULL;
    in->d_thread->priv = NULL;

    demux_flush(demuxer);
    assert(in->total_bytes == 0);

    if (in->owns_stream)
        free_stream(demuxer->stream);
    demuxer->stream = NULL;
}