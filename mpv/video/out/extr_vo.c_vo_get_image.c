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
struct vo {TYPE_2__* in; TYPE_1__* driver; } ;
struct mp_image {int dummy; } ;
struct TYPE_4__ {scalar_t__ dr_helper; } ;
struct TYPE_3__ {struct mp_image* (* get_image_ts ) (struct vo*,int,int,int,int) ;} ;

/* Variables and functions */
 struct mp_image* dr_helper_get_image (scalar_t__,int,int,int,int) ; 
 struct mp_image* stub1 (struct vo*,int,int,int,int) ; 

struct mp_image *vo_get_image(struct vo *vo, int imgfmt, int w, int h,
                              int stride_align)
{
    if (vo->driver->get_image_ts)
        return vo->driver->get_image_ts(vo, imgfmt, w, h, stride_align);
    if (vo->in->dr_helper)
        return dr_helper_get_image(vo->in->dr_helper, imgfmt, w, h, stride_align);
    return NULL;
}