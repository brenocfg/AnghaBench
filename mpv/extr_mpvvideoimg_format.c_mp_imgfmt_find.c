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
struct mp_imgfmt_desc {int id; int flags; int num_planes; int chroma_xs; int chroma_ys; int plane_bits; } ;

/* Variables and functions */
 int IMGFMT_END ; 
 int IMGFMT_START ; 
 int MP_IMGFLAG_NE ; 
 struct mp_imgfmt_desc mp_imgfmt_get_desc (int) ; 

int mp_imgfmt_find(int xs, int ys, int planes, int component_bits, int flags)
{
    for (int n = IMGFMT_START + 1; n < IMGFMT_END; n++) {
        struct mp_imgfmt_desc desc = mp_imgfmt_get_desc(n);
        if (desc.id && ((desc.flags & flags) == flags)) {
            if (desc.num_planes == planes && desc.chroma_xs == xs &&
                desc.chroma_ys == ys && desc.plane_bits == component_bits &&
                (desc.flags & MP_IMGFLAG_NE))
                return desc.id;
        }
    }
    return 0;
}