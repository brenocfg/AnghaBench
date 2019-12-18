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
struct nn_msgqueue_chunk {int dummy; } ;
struct TYPE_4__ {size_t pos; TYPE_2__* chunk; } ;
struct nn_msgqueue {scalar_t__ count; scalar_t__ mem; scalar_t__ maxmem; TYPE_1__ out; TYPE_2__* cache; } ;
struct nn_msg {int /*<<< orphan*/  body; int /*<<< orphan*/  sphdr; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ * msgs; } ;

/* Variables and functions */
 int EAGAIN ; 
 size_t NN_MSGQUEUE_GRANULARITY ; 
 int /*<<< orphan*/  alloc_assert (TYPE_2__*) ; 
 TYPE_2__* nn_alloc (int,char*) ; 
 size_t nn_chunkref_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_mv (int /*<<< orphan*/ *,struct nn_msg*) ; 
 scalar_t__ nn_slow (int) ; 

int nn_msgqueue_send (struct nn_msgqueue *self, struct nn_msg *msg)
{
    size_t msgsz;

    /*  By allowing one message of arbitrary size to be written to the queue,
        we allow even messages that exceed max buffer size to pass through.
        Beyond that we'll apply the buffer limit as specified by the user. */
    msgsz = nn_chunkref_size (&msg->sphdr) + nn_chunkref_size (&msg->body);
    if (nn_slow (self->count > 0 && self->mem + msgsz >= self->maxmem))
        return -EAGAIN;

    /*  Adjust the statistics. */
    ++self->count;
    self->mem += msgsz;

    /*  Move the content of the message to the pipe. */
    nn_msg_mv (&self->out.chunk->msgs [self->out.pos], msg);
    ++self->out.pos;

    /*  If there's no space for a new message in the pipe, either re-use
        the cache chunk or allocate a new chunk if it does not exist. */
    if (nn_slow (self->out.pos == NN_MSGQUEUE_GRANULARITY)) {
        if (nn_slow (!self->cache)) {
            self->cache = nn_alloc (sizeof (struct nn_msgqueue_chunk),
                "msgqueue chunk");
            alloc_assert (self->cache);
            self->cache->next = NULL;
        }
        self->out.chunk->next = self->cache;
        self->out.chunk = self->cache;
        self->cache = NULL;
        self->out.pos = 0;
    }

    return 0;
}