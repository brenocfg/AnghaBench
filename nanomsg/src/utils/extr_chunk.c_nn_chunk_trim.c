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
struct nn_chunk {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CHUNK_TAG ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 struct nn_chunk* nn_chunk_getptr (void*) ; 
 int /*<<< orphan*/  nn_putl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *nn_chunk_trim (void *p, size_t n)
{
    struct nn_chunk *self;
    const size_t hdrsz = sizeof (struct nn_chunk) + 2 * sizeof (uint32_t);
    size_t empty_space;

    self = nn_chunk_getptr (p);

    /*  Sanity check. We cannot trim more bytes than there are in the chunk. */
    nn_assert (n <= self->size);

    /*  Adjust the chunk header. */
    p = ((uint8_t*) p) + n;
    nn_putl ((uint8_t*) (((uint32_t*) p) - 1), NN_CHUNK_TAG);
    empty_space = (uint8_t*) p - (uint8_t*) self - hdrsz;
    nn_assert(empty_space < UINT32_MAX);
    nn_putl ((uint8_t*) (((uint32_t*) p) - 2), (uint32_t) empty_space);

    /*  Adjust the size of the message. */
    self->size -= n;

    return p;
}