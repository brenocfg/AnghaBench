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
struct nn_chunkref_chunk {void* chunk; } ;
struct TYPE_2__ {int* ref; } ;
struct nn_chunkref {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int nn_chunk_alloc (int,int /*<<< orphan*/ ,void**) ; 

void *nn_chunkref_getchunk (struct nn_chunkref *self)
{
    int rc;
    struct nn_chunkref_chunk *ch;
    void *chunk;

    if (self->u.ref [0] == 0xff) {
        ch = (struct nn_chunkref_chunk*) self;
        self->u.ref [0] = 0;
        return ch->chunk;
    }

    rc = nn_chunk_alloc (self->u.ref [0], 0, &chunk);
    errno_assert (rc == 0);
    memcpy (chunk, &self->u.ref [1], self->u.ref [0]);
    self->u.ref [0] = 0;
    return chunk;
}