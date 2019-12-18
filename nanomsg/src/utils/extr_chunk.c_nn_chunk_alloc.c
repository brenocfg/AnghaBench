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
struct nn_chunk {size_t size; int /*<<< orphan*/  ffn; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NN_CHUNK_TAG ; 
 struct nn_chunk* nn_alloc (size_t,char*) ; 
 int /*<<< orphan*/  nn_atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_chunk_default_free ; 
 void* nn_chunk_getdata (struct nn_chunk*) ; 
 size_t nn_chunk_hdrsize () ; 
 int /*<<< orphan*/  nn_putl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 

int nn_chunk_alloc (size_t size, int type, void **result)
{
    size_t sz;
    struct nn_chunk *self;
    const size_t hdrsz = nn_chunk_hdrsize ();

    /*  Compute total size to be allocated. Check for overflow. */
    sz = hdrsz + size;
    if (nn_slow (sz < hdrsz))
        return -ENOMEM;

    /*  Allocate the actual memory depending on the type. */
    switch (type) {
    case 0:
        self = nn_alloc (sz, "message chunk");
        break;
    default:
        return -EINVAL;
    }
    if (nn_slow (!self))
        return -ENOMEM;

    /*  Fill in the chunk header. */
    nn_atomic_init (&self->refcount, 1);
    self->size = size;
    self->ffn = nn_chunk_default_free;

    /*  Fill in the size of the empty space between the chunk header
        and the message. */
    nn_putl ((uint8_t*) ((uint32_t*) (self + 1)), 0);

    /*  Fill in the tag. */
    nn_putl ((uint8_t*) ((((uint32_t*) (self + 1))) + 1), NN_CHUNK_TAG);

    *result = nn_chunk_getdata (self);
    return 0;
}