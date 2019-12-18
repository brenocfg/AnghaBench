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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nn_chunk {int /*<<< orphan*/  (* ffn ) (struct nn_chunk*) ;int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CHUNK_TAG_DEALLOCATED ; 
 int nn_atomic_dec (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_atomic_term (int /*<<< orphan*/ *) ; 
 struct nn_chunk* nn_chunk_getptr (void*) ; 
 int /*<<< orphan*/  nn_putl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nn_chunk*) ; 

void nn_chunk_free (void *p)
{
    struct nn_chunk *self;

    self = nn_chunk_getptr (p);

    /*  Decrement the reference count. Actual deallocation happens only if
        it drops to zero. */
    if (nn_atomic_dec (&self->refcount, 1) <= 1) {

        /*  Mark chunk as deallocated. */
        nn_putl ((uint8_t*) (((uint32_t*) p) - 1), NN_CHUNK_TAG_DEALLOCATED);

        /*  Deallocate the resources held by the chunk. */
        nn_atomic_term (&self->refcount);

        /*  Deallocate the memory block according to the allocation
            mechanism specified. */
        self->ffn (self);
    }
}