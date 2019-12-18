#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpvs_fmt {scalar_t__ cw; scalar_t__ ch; scalar_t__ bits; } ;
struct mp_regular_imgfmt {scalar_t__ component_pad; scalar_t__ chroma_w; scalar_t__ chroma_h; int component_size; int num_planes; TYPE_1__* planes; } ;
struct TYPE_2__ {int num_components; int* components; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_get_regular_imgfmt (struct mp_regular_imgfmt*,int) ; 

__attribute__((used)) static bool compare_fmt(int imgfmt, const struct mpvs_fmt *vs)
{
    struct mp_regular_imgfmt rfmt;
    if (!mp_get_regular_imgfmt(&rfmt, imgfmt))
        return false;
    if (rfmt.component_pad > 0)
        return false;
    if (rfmt.chroma_w != vs->cw || rfmt.chroma_h != vs->ch)
        return false;
    if (rfmt.component_size * 8 + rfmt.component_pad != vs->bits)
        return false;
    if (rfmt.num_planes != 3)
        return false;
    for (int n = 0; n < 3; n++) {
        if (rfmt.planes[n].num_components != 1)
            return false;
        if (rfmt.planes[n].components[0] != n + 1)
            return false;
    }
    return true;
}