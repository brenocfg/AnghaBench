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
struct video_image {int hwdec_mapped; int /*<<< orphan*/  mpi; scalar_t__ id; int /*<<< orphan*/  planes; } ;
struct gl_video {scalar_t__ hwdec_mapper; scalar_t__ hwdec_active; struct video_image image; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gc_pending_dr_fences (struct gl_video*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_hwdec_mapper_unmap (scalar_t__) ; 

__attribute__((used)) static void unref_current_image(struct gl_video *p)
{
    struct video_image *vimg = &p->image;

    if (vimg->hwdec_mapped) {
        assert(p->hwdec_active && p->hwdec_mapper);
        ra_hwdec_mapper_unmap(p->hwdec_mapper);
        memset(vimg->planes, 0, sizeof(vimg->planes));
        vimg->hwdec_mapped = false;
    }

    vimg->id = 0;

    mp_image_unrefp(&vimg->mpi);

    // While we're at it, also garbage collect pending fences in here to
    // get it out of the way.
    gc_pending_dr_fences(p, false);
}