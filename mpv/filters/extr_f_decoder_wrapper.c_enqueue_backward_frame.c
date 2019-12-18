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
typedef  scalar_t__ uint64_t ;
struct priv {scalar_t__ reverse_queue_byte_size; int reverse_queue_complete; int /*<<< orphan*/  num_reverse_queue; int /*<<< orphan*/  reverse_queue; TYPE_1__* header; TYPE_2__* opt_cache; } ;
struct mp_frame {scalar_t__ type; } ;
struct MPOpts {scalar_t__ video_reverse_size; scalar_t__ audio_reverse_size; } ;
struct TYPE_4__ {struct MPOpts* opts; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct priv*,char*) ; 
 scalar_t__ MP_FRAME_EOF ; 
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_frame) ; 
#define  STREAM_AUDIO 129 
#define  STREAM_VIDEO 128 
 scalar_t__ mp_frame_approx_size (struct mp_frame) ; 
 int /*<<< orphan*/  mp_frame_unref (struct mp_frame*) ; 

__attribute__((used)) static void enqueue_backward_frame(struct priv *p, struct mp_frame frame)
{
    bool eof = frame.type == MP_FRAME_EOF;

    if (!eof) {
        struct MPOpts *opts = p->opt_cache->opts;

        uint64_t queue_size = 0;
        switch (p->header->type) {
        case STREAM_VIDEO: queue_size = opts->video_reverse_size; break;
        case STREAM_AUDIO: queue_size = opts->audio_reverse_size; break;
        }

        if (p->reverse_queue_byte_size >= queue_size) {
            MP_ERR(p, "Reversal queue overflow, discarding frame.\n");
            mp_frame_unref(&frame);
            return;
        }

        p->reverse_queue_byte_size += mp_frame_approx_size(frame);
    }

    // Note: EOF (really BOF) is propagated, but not reversed.
    MP_TARRAY_INSERT_AT(p, p->reverse_queue, p->num_reverse_queue,
                        eof ? 0 : p->num_reverse_queue, frame);

    p->reverse_queue_complete = eof;
}