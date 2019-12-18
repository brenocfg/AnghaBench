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
struct mp_image {int* stride; int /*<<< orphan*/ ** planes; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  imgfmt; } ;

/* Variables and functions */
 uintptr_t MP_ALIGN_UP (uintptr_t,int) ; 
 int MP_MAX_PLANES ; 
 int mp_image_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*,int*) ; 

__attribute__((used)) static bool mp_image_fill_alloc(struct mp_image *mpi, int stride_align,
                                void *buffer, int buffer_size)
{
    int stride[MP_MAX_PLANES];
    int plane_offset[MP_MAX_PLANES];
    int plane_size[MP_MAX_PLANES];
    int size = mp_image_layout(mpi->imgfmt, mpi->w, mpi->h, stride_align,
                               stride, plane_offset, plane_size);
    if (size < 0 || size > buffer_size)
        return false;

    int align = MP_ALIGN_UP((uintptr_t)buffer, stride_align) - (uintptr_t)buffer;
    if (buffer_size - size < align)
        return false;
    uint8_t *s = buffer;
    s += align;

    for (int n = 0; n < MP_MAX_PLANES; n++) {
        mpi->planes[n] = plane_offset[n] >= 0 ? s + plane_offset[n] : NULL;
        mpi->stride[n] = stride[n];
    }

    return true;
}