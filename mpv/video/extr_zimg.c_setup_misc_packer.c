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
struct mp_zimg_repack {scalar_t__ zimgfmt; int* components; scalar_t__ pack; int /*<<< orphan*/  packed_repack_scanline; int /*<<< orphan*/  repack; } ;
struct mp_regular_imgfmt {int component_size; int component_pad; int num_planes; int chroma_w; int chroma_h; int /*<<< orphan*/  planes; int /*<<< orphan*/  component_type; } ;

/* Variables and functions */
 scalar_t__ IMGFMT_RGB30 ; 
 int /*<<< orphan*/  MP_COMPONENT_TYPE_UINT ; 
 int mp_find_regular_imgfmt (struct mp_regular_imgfmt*) ; 
 int /*<<< orphan*/  pa_ccc10z2 ; 
 int /*<<< orphan*/  packed_repack ; 
 int /*<<< orphan*/  un_ccc10x2 ; 

__attribute__((used)) static void setup_misc_packer(struct mp_zimg_repack *r)
{
    // Although it's in regular_repackers[], the generic mpv imgfmt metadata
    // can't handle it yet.
    if (r->zimgfmt == IMGFMT_RGB30) {
        struct mp_regular_imgfmt planar10 = {
            .component_type = MP_COMPONENT_TYPE_UINT,
            .component_size = 2,
            .component_pad = -6,
            .num_planes = 3,
            .planes = {
                {1, {1}},
                {1, {2}},
                {1, {3}},
            },
            .chroma_w = 1,
            .chroma_h = 1,
        };
        int planar_fmt = mp_find_regular_imgfmt(&planar10);
        if (!planar_fmt)
            return;
        r->zimgfmt = planar_fmt;
        r->repack = packed_repack;
        r->packed_repack_scanline = r->pack ? pa_ccc10z2 : un_ccc10x2;
        static int c_order[] = {3, 2, 1};
        for (int n = 0; n < 3; n++)
            r->components[n] = c_order[n] - 1;
    }
}