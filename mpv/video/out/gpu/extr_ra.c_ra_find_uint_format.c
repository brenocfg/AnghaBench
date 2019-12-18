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
struct ra_format {scalar_t__ ctype; int num_components; int pixel_size; int* component_depth; } ;
struct ra {int num_formats; struct ra_format** formats; } ;

/* Variables and functions */
 scalar_t__ RA_CTYPE_UINT ; 
 scalar_t__ ra_format_is_regular (struct ra_format const*) ; 

const struct ra_format *ra_find_uint_format(struct ra *ra,
                                            int bytes_per_component,
                                            int n_components)
{
    for (int n = 0; n < ra->num_formats; n++) {
        const struct ra_format *fmt = ra->formats[n];
        if (fmt->ctype == RA_CTYPE_UINT && fmt->num_components == n_components &&
            fmt->pixel_size == bytes_per_component * n_components &&
            fmt->component_depth[0] == bytes_per_component * 8 &&
            ra_format_is_regular(fmt))
            return fmt;
    }
    return NULL;
}