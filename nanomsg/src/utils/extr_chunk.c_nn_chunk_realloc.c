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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int n; } ;
struct nn_chunk {size_t size; TYPE_1__ refcount; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NN_CHUNK_TAG ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 int nn_chunk_alloc (size_t,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  nn_chunk_free (void*) ; 
 int /*<<< orphan*/  nn_chunk_getdata (struct nn_chunk*) ; 
 struct nn_chunk* nn_chunk_getptr (void*) ; 
 size_t nn_chunk_hdrsize () ; 
 int /*<<< orphan*/  nn_putl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 

int nn_chunk_realloc (size_t size, void **chunk)
{
    struct nn_chunk *self;
    void *new_ptr;
    size_t hdr_size;
    int rc;
    void *p = *chunk;

    self = nn_chunk_getptr (p);

    /*  Check if we only have one reference to this object, in that case we can
        reallocate the memory chunk. */
    if (self->refcount.n == 1) {

         size_t grow;
         size_t empty;

        /*  If the new size is smaller than the old size, we can just keep
            it.  Avoid an allocation.  We'll have wasted & lost data
            at the end, but who cares.  This is basically "chop". */
        if (size <= self->size) {
            self->size = size;
            return (0);
        }

        hdr_size = nn_chunk_hdrsize ();
        empty = (uint8_t*) p - (uint8_t*) self - hdr_size;
        grow = size - self->size;

        /* Check for overflow. */
        if (hdr_size + size < size) {
            return -ENOMEM;
	}

        /* Can we grow into empty space? */
        if (grow <= empty) {
            new_ptr = (uint8_t *)p - grow;
            memmove (new_ptr, p, self->size);
            self->size = size;

            /*  Recalculate the size of empty space, and reconstruct
                the tag and prefix. */
            empty = (uint8_t *)new_ptr - (uint8_t *)self - hdr_size;
            nn_putl ((uint8_t*) (((uint32_t*) new_ptr) - 1), NN_CHUNK_TAG);
            nn_putl ((uint8_t*) (((uint32_t*) new_ptr) - 2), (uint32_t) empty);
            *chunk = p;
            return (0);
        }
    }

    /*  There are either multiple references to this memory chunk,
        or we cannot reuse the existing space.  We create a new one
        copy the data.  (This is no worse than nn_realloc, btw.) */
    new_ptr = NULL;
    rc = nn_chunk_alloc (size, 0, &new_ptr);

    if (nn_slow (rc != 0)) {
        return rc;
    }

    memcpy (new_ptr, nn_chunk_getdata (self), self->size);
    *chunk = new_ptr;
    nn_chunk_free (p);

    return 0;
}