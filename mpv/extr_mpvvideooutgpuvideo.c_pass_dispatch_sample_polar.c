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
typedef  int uint64_t ;
struct scaler {TYPE_1__* kernel; } ;
struct image {float w; float h; int components; } ;
struct gl_video {TYPE_2__* ra; int /*<<< orphan*/  sc; } ;
struct TYPE_4__ {int caps; int max_shmem; } ;
struct TYPE_3__ {int radius_cutoff; } ;

/* Variables and functions */
 int RA_CAP_COMPUTE ; 
 int RA_CAP_GATHER ; 
 int ceil (int) ; 
 int /*<<< orphan*/  pass_compute_polar (int /*<<< orphan*/ ,struct scaler*,int,int,int,int,int) ; 
 int /*<<< orphan*/  pass_is_compute (struct gl_video*,int,int,int) ; 
 int /*<<< orphan*/  pass_sample_polar (int /*<<< orphan*/ ,struct scaler*,int,int) ; 

__attribute__((used)) static void pass_dispatch_sample_polar(struct gl_video *p, struct scaler *scaler,
                                       struct image img, int w, int h)
{
    uint64_t reqs = RA_CAP_COMPUTE;
    if ((p->ra->caps & reqs) != reqs)
        goto fallback;

    int bound = ceil(scaler->kernel->radius_cutoff);
    int offset = bound - 1; // padding top/left
    int padding = offset + bound; // total padding

    float ratiox = (float)w / img.w,
          ratioy = (float)h / img.h;

    // For performance we want to load at least as many pixels
    // horizontally as there are threads in a warp (32 for nvidia), as
    // well as enough to take advantage of shmem parallelism
    const int warp_size = 32, threads = 256;
    int bw = warp_size;
    int bh = threads / bw;

    // We need to sample everything from base_min to base_max, so make sure
    // we have enough room in shmem
    int iw = (int)ceil(bw / ratiox) + padding + 1,
        ih = (int)ceil(bh / ratioy) + padding + 1;

    int shmem_req = iw * ih * img.components * sizeof(float);
    if (shmem_req > p->ra->max_shmem)
        goto fallback;

    pass_is_compute(p, bw, bh, false);
    pass_compute_polar(p->sc, scaler, img.components, bw, bh, iw, ih);
    return;

fallback:
    // Fall back to regular polar shader when compute shaders are unsupported
    // or the kernel is too big for shmem
    pass_sample_polar(p->sc, scaler, img.components,
                      p->ra->caps & RA_CAP_GATHER);
}