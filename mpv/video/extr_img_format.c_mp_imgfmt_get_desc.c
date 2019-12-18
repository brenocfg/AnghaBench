#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_imgfmt_desc {int id; int avformat; int chroma_xs; int chroma_ys; int* bpp; int component_bits; int num_planes; int plane_bits; int flags; int* bytes; int* xs; int* ys; int align_x; int align_y; } ;
typedef  enum mp_component_type { ____Placeholder_mp_component_type } mp_component_type ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {size_t plane; int step; int depth; int shift; } ;
struct TYPE_4__ {int nb_components; int log2_chroma_w; int log2_chroma_h; int flags; TYPE_2__* comp; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVComponentDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int AV_PIX_FMT_FLAG_BE ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int AV_PIX_FMT_MONOBLACK ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_PAL8 ; 
 int AV_PIX_FMT_UYYVYY411 ; 
 int AV_PIX_FMT_XYZ12BE ; 
 int AV_PIX_FMT_XYZ12LE ; 
 scalar_t__ MP_COMPONENT_TYPE_UINT ; 
 int MP_IMGFLAG_ALPHA ; 
 int MP_IMGFLAG_BE ; 
 int MP_IMGFLAG_BYTE_ALIGNED ; 
 int MP_IMGFLAG_HWACCEL ; 
 int MP_IMGFLAG_LE ; 
 int MP_IMGFLAG_PAL ; 
 int MP_IMGFLAG_RGB ; 
 int MP_IMGFLAG_RGB_P ; 
 int MP_IMGFLAG_YUV ; 
 int MP_IMGFLAG_YUV_NV ; 
 int MP_IMGFLAG_YUV_P ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int imgfmt2pixfmt (int) ; 
 scalar_t__ mp_imgfmt_get_component_type (int) ; 
 struct mp_imgfmt_desc mp_only_imgfmt_desc (int) ; 

struct mp_imgfmt_desc mp_imgfmt_get_desc(int mpfmt)
{
    enum AVPixelFormat fmt = imgfmt2pixfmt(mpfmt);
    const AVPixFmtDescriptor *pd = av_pix_fmt_desc_get(fmt);
    if (!pd || pd->nb_components > 4 || fmt == AV_PIX_FMT_NONE ||
        fmt == AV_PIX_FMT_UYYVYY411)
        return mp_only_imgfmt_desc(mpfmt);
    enum mp_component_type is_uint =
        mp_imgfmt_get_component_type(mpfmt) == MP_COMPONENT_TYPE_UINT;

    struct mp_imgfmt_desc desc = {
        .id = mpfmt,
        .avformat = fmt,
        .chroma_xs = pd->log2_chroma_w,
        .chroma_ys = pd->log2_chroma_h,
    };

    int planedepth[4] = {0};
    int el_size = (pd->flags & AV_PIX_FMT_FLAG_BITSTREAM) ? 1 : 8;
    bool need_endian = false; // single component is spread over >1 bytes
    int shift = -1; // shift for all components, or -1 if not uniform
    for (int c = 0; c < pd->nb_components; c++) {
        AVComponentDescriptor d = pd->comp[c];
        // multiple components per plane -> Y is definitive, ignore chroma
        if (!desc.bpp[d.plane])
            desc.bpp[d.plane] = d.step * el_size;
        planedepth[d.plane] += d.depth;
        need_endian |= (d.depth + d.shift) > 8;
        if (c == 0)
            desc.component_bits = d.depth;
        if (d.depth != desc.component_bits)
            desc.component_bits = 0;
        if (c == 0)
            shift = d.shift;
        if (shift != d.shift)
            shift = -1;
    }

    for (int p = 0; p < 4; p++) {
        if (desc.bpp[p])
            desc.num_planes++;
    }

    desc.plane_bits = planedepth[0];

    // Check whether any components overlap other components (per plane).
    // We're cheating/simplifying here: we assume that this happens if a shift
    // is set - which is wrong in general (could be needed for padding, instead
    // of overlapping bits of another component - use the "< 8" test to exclude
    // "normal" formats which use this for padding, like p010).
    // Needed for rgb444le/be.
    bool component_byte_overlap = false;
    for (int c = 0; c < pd->nb_components; c++) {
        AVComponentDescriptor d = pd->comp[c];
        component_byte_overlap |= d.shift > 0 && planedepth[d.plane] > 8 &&
                                  desc.component_bits < 8;
    }

    // If every component sits in its own byte, or all components are within
    // a single byte, no endian-dependent access is needed. If components
    // stride bytes (like with packed 2 byte RGB formats), endian-dependent
    // access is needed.
    need_endian |= component_byte_overlap;

    if (!need_endian) {
        desc.flags |= MP_IMGFLAG_LE | MP_IMGFLAG_BE;
    } else {
        desc.flags |= (pd->flags & AV_PIX_FMT_FLAG_BE)
                      ? MP_IMGFLAG_BE : MP_IMGFLAG_LE;
    }

    if ((pd->flags & AV_PIX_FMT_FLAG_HWACCEL)) {
        desc.flags |= MP_IMGFLAG_HWACCEL;
    } else if (fmt == AV_PIX_FMT_XYZ12LE || fmt == AV_PIX_FMT_XYZ12BE) {
        /* nothing */
    } else if (!(pd->flags & AV_PIX_FMT_FLAG_RGB) &&
               fmt != AV_PIX_FMT_MONOBLACK &&
               fmt != AV_PIX_FMT_PAL8)
    {
        desc.flags |= MP_IMGFLAG_YUV;
    } else {
        desc.flags |= MP_IMGFLAG_RGB;
    }

    if (pd->flags & AV_PIX_FMT_FLAG_ALPHA)
        desc.flags |= MP_IMGFLAG_ALPHA;

    if (!(pd->flags & AV_PIX_FMT_FLAG_HWACCEL) &&
        !(pd->flags & AV_PIX_FMT_FLAG_BITSTREAM))
    {
        desc.flags |= MP_IMGFLAG_BYTE_ALIGNED;
        for (int p = 0; p < desc.num_planes; p++)
            desc.bytes[p] = desc.bpp[p] / 8;
    }

    if (pd->flags & AV_PIX_FMT_FLAG_PAL)
        desc.flags |= MP_IMGFLAG_PAL;

    if ((desc.flags & (MP_IMGFLAG_YUV | MP_IMGFLAG_RGB))
        && (desc.flags & MP_IMGFLAG_BYTE_ALIGNED)
        && !(pd->flags & AV_PIX_FMT_FLAG_PAL)
        && !component_byte_overlap
        && shift >= 0 && is_uint)
    {
        bool same_depth = true;
        for (int p = 0; p < desc.num_planes; p++) {
            same_depth &= planedepth[p] == planedepth[0] &&
                          desc.bpp[p] == desc.bpp[0];
        }
        if (same_depth && pd->nb_components == desc.num_planes) {
            if (desc.flags & MP_IMGFLAG_YUV) {
                desc.flags |= MP_IMGFLAG_YUV_P;
            } else {
                desc.flags |= MP_IMGFLAG_RGB_P;
            }
        }
        if (pd->nb_components == 3 && desc.num_planes == 2 &&
            planedepth[1] == planedepth[0] * 2 &&
            desc.bpp[1] == desc.bpp[0] * 2 &&
            (desc.flags & MP_IMGFLAG_YUV))
        {

            desc.flags |= MP_IMGFLAG_YUV_NV;
        }
        if (desc.flags & (MP_IMGFLAG_YUV_P | MP_IMGFLAG_RGB_P | MP_IMGFLAG_YUV_NV))
            desc.component_bits += shift;
    }

    for (int p = 0; p < desc.num_planes; p++) {
        desc.xs[p] = (p == 1 || p == 2) ? desc.chroma_xs : 0;
        desc.ys[p] = (p == 1 || p == 2) ? desc.chroma_ys : 0;
    }

    desc.align_x = 1 << desc.chroma_xs;
    desc.align_y = 1 << desc.chroma_ys;

    if ((desc.bpp[0] % 8) != 0)
        desc.align_x = 8 / desc.bpp[0]; // expect power of 2

    if (desc.flags & MP_IMGFLAG_HWACCEL) {
        desc.component_bits = 0;
        desc.plane_bits = 0;
    }

    return desc;
}