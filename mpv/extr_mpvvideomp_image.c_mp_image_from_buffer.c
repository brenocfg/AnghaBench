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
struct mp_image {int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ *,int,void (*) (void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_fill_alloc (struct mp_image*,int,int /*<<< orphan*/ *,int) ; 
 struct mp_image* mp_image_new_dummy_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int,int) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

struct mp_image *mp_image_from_buffer(int imgfmt, int w, int h, int stride_align,
                                      uint8_t *buffer, int buffer_size,
                                      void *free_opaque,
                                      void (*free)(void *opaque, uint8_t *data))
{
    struct mp_image *mpi = mp_image_new_dummy_ref(NULL);
    mp_image_setfmt(mpi, imgfmt);
    mp_image_set_size(mpi, w, h);

    if (!mp_image_fill_alloc(mpi, stride_align, buffer, buffer_size))
        goto fail;

    mpi->bufs[0] = av_buffer_create(buffer, buffer_size, free, free_opaque, 0);
    if (!mpi->bufs[0])
        goto fail;

    return mpi;

fail:
    talloc_free(mpi);
    return NULL;
}