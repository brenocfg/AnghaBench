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
struct vo {TYPE_1__* driver; } ;
struct mp_image {int dummy; } ;
struct TYPE_2__ {struct mp_image* (* get_image ) (struct vo*,int,int,int,int) ;} ;

/* Variables and functions */
 struct mp_image* stub1 (struct vo*,int,int,int,int) ; 

__attribute__((used)) static struct mp_image *get_image_vo(void *ctx, int imgfmt, int w, int h,
                                     int stride_align)
{
    struct vo *vo = ctx;
    return vo->driver->get_image(vo, imgfmt, w, h, stride_align);
}