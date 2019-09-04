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
struct ra_imgfmt_desc {TYPE_1__** planes; int /*<<< orphan*/  num_planes; } ;
struct gl_video {scalar_t__ forced_dumb_mode; } ;
struct TYPE_2__ {scalar_t__ ctype; } ;

/* Variables and functions */
 scalar_t__ RA_CTYPE_UINT ; 

__attribute__((used)) static bool is_imgfmt_desc_supported(struct gl_video *p,
                                     const struct ra_imgfmt_desc *desc)
{
    if (!desc->num_planes)
        return false;

    if (desc->planes[0]->ctype == RA_CTYPE_UINT && p->forced_dumb_mode)
        return false;

    return true;
}