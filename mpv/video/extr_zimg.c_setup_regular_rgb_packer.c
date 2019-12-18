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
struct regular_repacker {void (* pa_scanline ) (void*,void**,int,int) ;void (* un_scanline ) (void*,void**,int,int) ;int packed_width; int component_width; int num_components; int prepadding; } ;
struct mp_zimg_repack {int zimgfmt; void (* packed_repack_scanline ) (void*,void**,int,int) ;int* components; int /*<<< orphan*/  repack; scalar_t__ pack; } ;
struct mp_regular_imgfmt_plane {int num_components; int* components; } ;
struct mp_regular_imgfmt {int num_planes; int component_size; scalar_t__ component_pad; struct mp_regular_imgfmt_plane* planes; scalar_t__ forced_csp; } ;

/* Variables and functions */
 int MPMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int MP_ARRAY_SIZE (struct regular_repacker*) ; 
 int mp_find_regular_imgfmt (struct mp_regular_imgfmt*) ; 
 int /*<<< orphan*/  mp_get_regular_imgfmt (struct mp_regular_imgfmt*,int) ; 
 int /*<<< orphan*/  packed_repack ; 
 struct regular_repacker* regular_repackers ; 

__attribute__((used)) static void setup_regular_rgb_packer(struct mp_zimg_repack *r)
{
    struct mp_regular_imgfmt desc;
    if (!mp_get_regular_imgfmt(&desc, r->zimgfmt))
        return;

    if (desc.num_planes != 1 || desc.planes[0].num_components < 3)
        return;
    struct mp_regular_imgfmt_plane *p = &desc.planes[0];

    for (int n = 0; n < p->num_components; n++) {
        if (p->components[n] >= 4) // no alpha
            return;
    }

    // padding must be in MSB or LSB
    if (p->components[0] && p->components[3])
        return;

    int depth = desc.component_size * 8 + MPMIN(0, desc.component_pad);

    // Find a physically compatible planar format (typically IMGFMT_420P).
    struct mp_regular_imgfmt desc2 = desc;
    desc2.forced_csp = 0;
    if (desc2.component_pad > 0)
        desc2.component_pad = 0;
    desc2.num_planes = 3;
    for (int n = 0; n < desc2.num_planes; n++) {
        desc2.planes[n].num_components = 1;
        desc2.planes[n].components[0] = n + 1;
    }
    int planar_fmt = mp_find_regular_imgfmt(&desc2);
    if (!planar_fmt)
        return;

    for (int i = 0; i < MP_ARRAY_SIZE(regular_repackers); i++) {
        const struct regular_repacker *pa = &regular_repackers[i];

        // The following may assume little endian (because some repack backends
        // use word access, while the metadata here uses byte access).

        int prepad = p->components[0] ? 0 : 8;
        int first_comp = p->components[0] ? 0 : 1;
        void (*repack_cb)(void *p1, void *p2[], int x0, int x1) =
            r->pack ? pa->pa_scanline : pa->un_scanline;

        if (pa->packed_width != desc.component_size * p->num_components * 8 ||
            pa->component_width != depth ||
            pa->num_components != 3 ||
            pa->prepadding != prepad ||
            !repack_cb)
            continue;

        r->repack = packed_repack;
        r->packed_repack_scanline = repack_cb;
        r->zimgfmt = planar_fmt;
        for (int n = 0; n < 3; n++)
            r->components[n] = p->components[first_comp + n] - 1;
        return;
    }
}