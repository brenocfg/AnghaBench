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
struct mp_regular_imgfmt {scalar_t__ component_type; scalar_t__ component_size; scalar_t__ num_planes; scalar_t__ component_pad; scalar_t__ forced_csp; scalar_t__ chroma_w; scalar_t__ chroma_h; TYPE_1__* planes; } ;
struct TYPE_2__ {int num_components; scalar_t__* components; } ;

/* Variables and functions */

__attribute__((used)) static bool regular_imgfmt_equals(struct mp_regular_imgfmt *a,
                                  struct mp_regular_imgfmt *b)
{
    if (a->component_type != b->component_type ||
        a->component_size != b->component_size ||
        a->num_planes     != b->num_planes ||
        a->component_pad  != b->component_pad ||
        a->forced_csp     != b->forced_csp ||
        a->chroma_w       != b->chroma_w ||
        a->chroma_h       != b->chroma_h)
        return false;

    for (int n = 0; n < a->num_planes; n++) {
        int num_comps = a->planes[n].num_components;
        if (num_comps != b->planes[n].num_components)
            return false;
        for (int i = 0; i < num_comps; i++) {
            if (a->planes[n].components[i] != b->planes[n].components[i])
                return false;
        }
    }

    return true;
}