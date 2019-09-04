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
struct ra_hwdec_mapper {TYPE_1__* driver; int /*<<< orphan*/  src; } ;
struct mp_image {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* map ) (struct ra_hwdec_mapper*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_setrefp (int /*<<< orphan*/ *,struct mp_image*) ; 
 int /*<<< orphan*/  ra_hwdec_mapper_unmap (struct ra_hwdec_mapper*) ; 
 scalar_t__ stub1 (struct ra_hwdec_mapper*) ; 

int ra_hwdec_mapper_map(struct ra_hwdec_mapper *mapper, struct mp_image *img)
{
    ra_hwdec_mapper_unmap(mapper);
    mp_image_setrefp(&mapper->src, img);
    if (mapper->driver->map(mapper) < 0) {
        ra_hwdec_mapper_unmap(mapper);
        return -1;
    }
    return 0;
}