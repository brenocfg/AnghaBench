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
struct ra_format {int dummy; } ;
struct ra {int dummy; } ;
typedef  enum mp_component_type { ____Placeholder_mp_component_type } mp_component_type ;

/* Variables and functions */
#define  MP_COMPONENT_TYPE_FLOAT 129 
#define  MP_COMPONENT_TYPE_UINT 128 
 struct ra_format const* ra_find_float_format (struct ra*,int,int) ; 
 struct ra_format const* ra_find_uint_format (struct ra*,int,int) ; 
 struct ra_format* ra_find_unorm_format (struct ra*,int,int) ; 

__attribute__((used)) static const struct ra_format *find_plane_format(struct ra *ra, int bytes,
                                                 int n_channels,
                                                 enum mp_component_type ctype)
{
    switch (ctype) {
    case MP_COMPONENT_TYPE_UINT: {
        const struct ra_format *f = ra_find_unorm_format(ra, bytes, n_channels);
        if (f)
            return f;
        return ra_find_uint_format(ra, bytes, n_channels);
    }
    case MP_COMPONENT_TYPE_FLOAT:
        return ra_find_float_format(ra, bytes, n_channels);
    default: return NULL;
    }
}