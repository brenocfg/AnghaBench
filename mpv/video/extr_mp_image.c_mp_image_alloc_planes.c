#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_image {TYPE_1__** bufs; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  imgfmt; int /*<<< orphan*/ * planes; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int MP_IMAGE_BYTE_ALIGN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* av_buffer_alloc (int) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_1__**) ; 
 int /*<<< orphan*/  mp_image_fill_alloc (struct mp_image*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_image_get_alloc_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mp_image_alloc_planes(struct mp_image *mpi)
{
    assert(!mpi->planes[0]);
    assert(!mpi->bufs[0]);

    int align = MP_IMAGE_BYTE_ALIGN;

    int size = mp_image_get_alloc_size(mpi->imgfmt, mpi->w, mpi->h, align);
    if (size < 0)
        return false;

    // Note: mp_image_pool assumes this creates only 1 AVBufferRef.
    mpi->bufs[0] = av_buffer_alloc(size + align);
    if (!mpi->bufs[0])
        return false;

    if (!mp_image_fill_alloc(mpi, align, mpi->bufs[0]->data, mpi->bufs[0]->size)) {
        av_buffer_unref(&mpi->bufs[0]);
        return false;
    }

    return true;
}