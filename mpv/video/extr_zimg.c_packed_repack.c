#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mp_zimg_repack {int* components; unsigned int* zmask; int /*<<< orphan*/  (* packed_repack_scanline ) (int /*<<< orphan*/ *,void**,unsigned int,unsigned int) ;TYPE_2__* tmp; TYPE_1__* mpi; } ;
typedef  int ptrdiff_t ;
struct TYPE_4__ {int* stride; void** planes; } ;
struct TYPE_3__ {int* stride; scalar_t__* planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**,unsigned int,unsigned int) ; 

__attribute__((used)) static int packed_repack(void *user, unsigned i, unsigned x0, unsigned x1)
{
    struct mp_zimg_repack *r = user;

    uint32_t *p1 =
        (void *)(r->mpi->planes[0] + r->mpi->stride[0] * (ptrdiff_t)i);

    void *p2[3];
    for (int p = 0; p < 3; p++) {
        int s = r->components[p];
        p2[p] = r->tmp->planes[s] +
                r->tmp->stride[s] * (ptrdiff_t)(i & r->zmask[s]);
    }

    r->packed_repack_scanline(p1, p2, x0, x1);

    return 0;
}