#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_regular_imgfmt_plane {int num_components; int* components; } ;
struct mp_regular_imgfmt {int component_size; int num_planes; int component_pad; int chroma_w; int chroma_h; int /*<<< orphan*/  forced_csp; struct mp_regular_imgfmt_plane* planes; int /*<<< orphan*/  component_type; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int depth; int shift; size_t plane; int step; int offset; } ;
struct TYPE_5__ {int flags; int nb_components; int log2_chroma_w; int log2_chroma_h; TYPE_2__* comp; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVComponentDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int AV_PIX_FMT_FLAG_BAYER ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int MPMAX (int,size_t) ; 
 size_t MP_MAX_PLANES ; 
 int MP_NUM_COMPONENTS ; 
 TYPE_1__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgfmt2pixfmt (int) ; 
 int /*<<< orphan*/  is_native_endian (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mp_imgfmt_get_component_type (int) ; 
 int /*<<< orphan*/  mp_imgfmt_get_forced_csp (int) ; 
 int /*<<< orphan*/  validate_regular_imgfmt (struct mp_regular_imgfmt*) ; 

bool mp_get_regular_imgfmt(struct mp_regular_imgfmt *dst, int imgfmt)
{
    struct mp_regular_imgfmt res = {0};

    const AVPixFmtDescriptor *pixdesc =
        av_pix_fmt_desc_get(imgfmt2pixfmt(imgfmt));

    if (!pixdesc || (pixdesc->flags & AV_PIX_FMT_FLAG_BITSTREAM) ||
        (pixdesc->flags & AV_PIX_FMT_FLAG_HWACCEL) ||
        (pixdesc->flags & AV_PIX_FMT_FLAG_PAL) ||
        pixdesc->nb_components < 1 ||
        pixdesc->nb_components > MP_NUM_COMPONENTS ||
        !is_native_endian(pixdesc))
        return false;

    res.component_type = mp_imgfmt_get_component_type(imgfmt);
    if (!res.component_type)
        return false;

    const AVComponentDescriptor *comp0 = &pixdesc->comp[0];

    int depth = comp0->depth + comp0->shift;
    if (depth < 1 || depth > 64)
        return false;
    res.component_size = (depth + 7) / 8;

    for (int n = 0; n < pixdesc->nb_components; n++) {
        const AVComponentDescriptor *comp = &pixdesc->comp[n];

        if (comp->plane < 0 || comp->plane >= MP_MAX_PLANES)
            return false;

        res.num_planes = MPMAX(res.num_planes, comp->plane + 1);

        // We support uniform depth only.
        if (comp->depth != comp0->depth || comp->shift != comp0->shift)
            return false;

        // Uniform component size; even the padding must have same size.
        int ncomp = comp->step / res.component_size;
        if (!ncomp || ncomp * res.component_size != comp->step)
            return false;

        struct mp_regular_imgfmt_plane *plane = &res.planes[comp->plane];

        if (plane->num_components && plane->num_components != ncomp)
            return false;
        plane->num_components = ncomp;

        int pos = comp->offset / res.component_size;
        if (pos < 0 || pos >= ncomp || ncomp > MP_NUM_COMPONENTS)
            return false;
        if (plane->components[pos])
            return false;
        plane->components[pos] = n + 1;
    }

    // Make sure alpha is always component 4.
    if (pixdesc->nb_components == 2 && (pixdesc->flags & AV_PIX_FMT_FLAG_ALPHA)) {
        for (int n = 0; n < res.num_planes; n++) {
            for (int i = 0; i < res.planes[n].num_components; i++) {
                if (res.planes[n].components[i] == 2)
                    res.planes[n].components[i] = 4;
            }
        }
    }

    res.component_pad = comp0->depth - res.component_size * 8;
    if (comp0->shift) {
        // We support padding only on 1 side.
        if (comp0->shift + comp0->depth != res.component_size * 8)
            return false;
        res.component_pad = -res.component_pad;
    }

    res.chroma_w = 1 << pixdesc->log2_chroma_w;
    res.chroma_h = 1 << pixdesc->log2_chroma_h;

#if LIBAVUTIL_VERSION_MICRO >= 100
    if (pixdesc->flags & AV_PIX_FMT_FLAG_BAYER)
        return false; // it's satan himself
#endif

    res.forced_csp = mp_imgfmt_get_forced_csp(imgfmt);

    if (!validate_regular_imgfmt(&res))
        return false;

    *dst = res;
    return true;
}