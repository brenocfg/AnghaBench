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
typedef  int /*<<< orphan*/  uint32_t ;
struct mp_zimg_repack {int* zmask; int* components; int /*<<< orphan*/  (* packed_repack_scanline ) (int /*<<< orphan*/ *,void**,unsigned int,unsigned int) ;TYPE_3__* tmp; TYPE_2__* mpi; scalar_t__ pack; scalar_t__* use_buf; } ;
typedef  unsigned int ptrdiff_t ;
struct TYPE_6__ {unsigned int* stride; void** planes; } ;
struct TYPE_4__ {int chroma_xs; int chroma_ys; unsigned int* bytes; } ;
struct TYPE_5__ {unsigned int* stride; void** planes; TYPE_1__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**,unsigned int,unsigned int) ; 

__attribute__((used)) static int repack_nv(void *user, unsigned i, unsigned x0, unsigned x1)
{
    struct mp_zimg_repack *r = user;

    int xs = r->mpi->fmt.chroma_xs;
    int ys = r->mpi->fmt.chroma_ys;

    if (r->use_buf[0]) {
        // Copy Y.
        int l_h = 1 << ys;
        for (int y = i; y < i + l_h; y++) {
            ptrdiff_t bpp = r->mpi->fmt.bytes[0];
            void *a = r->mpi->planes[0] +
                    r->mpi->stride[0] * (ptrdiff_t)y + bpp * x0;
            void *b = r->tmp->planes[0] +
                    r->tmp->stride[0] * (ptrdiff_t)(y & r->zmask[0]) + bpp * x0;
            size_t size = (x1 - x0) * bpp;
            if (r->pack) {
                memcpy(a, b, size);
            } else {
                memcpy(b, a, size);
            }
        }
    }

    uint32_t *p1 =
        (void *)(r->mpi->planes[1] + r->mpi->stride[1] * (ptrdiff_t)(i >> ys));

    void *p2[2];
    for (int p = 0; p < 2; p++) {
        int s = r->components[p];
        p2[p] = r->tmp->planes[s] +
                r->tmp->stride[s] * (ptrdiff_t)((i >> ys) & r->zmask[s]);
    }

    r->packed_repack_scanline(p1, p2, x0 >> xs, x1 >> xs);

    return 0;
}