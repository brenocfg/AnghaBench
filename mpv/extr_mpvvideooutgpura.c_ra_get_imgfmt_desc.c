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
struct ra_imgfmt_desc {int num_planes; int component_bits; scalar_t__ component_pad; int /*<<< orphan*/  chroma_h; int /*<<< orphan*/  chroma_w; TYPE_2__** planes; int /*<<< orphan*/ ** components; int /*<<< orphan*/  member_0; } ;
struct ra {int num_formats; TYPE_1__** formats; } ;
struct mp_regular_imgfmt_plane {int num_components; int /*<<< orphan*/ * components; } ;
struct mp_regular_imgfmt {int num_planes; int component_size; scalar_t__ component_pad; int /*<<< orphan*/  chroma_h; int /*<<< orphan*/  chroma_w; int /*<<< orphan*/  component_type; struct mp_regular_imgfmt_plane* planes; } ;
typedef  enum ra_ctype { ____Placeholder_ra_ctype } ra_ctype ;
struct TYPE_4__ {scalar_t__* component_depth; int ctype; } ;
struct TYPE_3__ {int special_imgfmt; struct ra_imgfmt_desc* special_imgfmt_desc; } ;

/* Variables and functions */
 int RA_CTYPE_UNKNOWN ; 
 TYPE_2__* find_plane_format (struct ra*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_get_regular_imgfmt (struct mp_regular_imgfmt*,int) ; 

bool ra_get_imgfmt_desc(struct ra *ra, int imgfmt, struct ra_imgfmt_desc *out)
{
    struct ra_imgfmt_desc res = {0};

    struct mp_regular_imgfmt regfmt;
    if (mp_get_regular_imgfmt(&regfmt, imgfmt)) {
        enum ra_ctype ctype = RA_CTYPE_UNKNOWN;
        res.num_planes = regfmt.num_planes;
        res.component_bits = regfmt.component_size * 8;
        res.component_pad = regfmt.component_pad;
        for (int n = 0; n < regfmt.num_planes; n++) {
            struct mp_regular_imgfmt_plane *plane = &regfmt.planes[n];
            res.planes[n] = find_plane_format(ra, regfmt.component_size,
                                              plane->num_components,
                                              regfmt.component_type);
            if (!res.planes[n])
                return false;
            for (int i = 0; i < plane->num_components; i++)
                res.components[n][i] = plane->components[i];
            // Dropping LSBs when shifting will lead to dropped MSBs.
            if (res.component_bits > res.planes[n]->component_depth[0] &&
                res.component_pad < 0)
                return false;
            // Renderer restriction, but actually an unwanted corner case.
            if (ctype != RA_CTYPE_UNKNOWN && ctype != res.planes[n]->ctype)
                return false;
            ctype = res.planes[n]->ctype;
        }
        res.chroma_w = regfmt.chroma_w;
        res.chroma_h = regfmt.chroma_h;
        goto supported;
    }

    for (int n = 0; n < ra->num_formats; n++) {
        if (imgfmt && ra->formats[n]->special_imgfmt == imgfmt) {
            res = *ra->formats[n]->special_imgfmt_desc;
            goto supported;
        }
    }

    // Unsupported format
    return false;

supported:

    *out = res;
    return true;
}