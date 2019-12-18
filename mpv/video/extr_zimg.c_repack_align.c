#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_zimg_repack {int* zmask; scalar_t__ pack; TYPE_3__* tmp; TYPE_2__* mpi; int /*<<< orphan*/ * use_buf; } ;
typedef  int ptrdiff_t ;
struct TYPE_6__ {int* stride; void** planes; } ;
struct TYPE_4__ {int num_planes; int* bytes; int* xs; int* ys; int chroma_ys; } ;
struct TYPE_5__ {int* stride; void** planes; TYPE_1__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int repack_align(void *user, unsigned i, unsigned x0, unsigned x1)
{
    struct mp_zimg_repack *r = user;

    for (int p = 0; p < r->mpi->fmt.num_planes; p++) {
        if (!r->use_buf[p])
            continue;

        int bpp = r->mpi->fmt.bytes[p];
        int xs = r->mpi->fmt.xs[p];
        int ys = r->mpi->fmt.ys[p];
        // Number of lines on this plane.
        int h = (1 << r->mpi->fmt.chroma_ys) - (1 << ys) + 1;

        for (int y = i; y < i + h; y++) {
            void *a = r->mpi->planes[p] +
                      r->mpi->stride[p] * (ptrdiff_t)(y >> ys) +
                      bpp * (x0 >> xs);
            void *b = r->tmp->planes[p] +
                      r->tmp->stride[p] * (ptrdiff_t)((y >> ys) & r->zmask[p]) +
                      bpp * (x0 >> xs);
            size_t size = ((x1 - x0) >> xs) * bpp;
            if (r->pack) {
                memcpy(a, b, size);
            } else {
                memcpy(b, a, size);
            }
        }
    }

    return 0;
}