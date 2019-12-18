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
struct vb2_queue {unsigned int num_buffers; } ;
struct TYPE_2__ {scalar_t__ field; unsigned int sizeimage; } ;
struct skeleton {scalar_t__ field; TYPE_1__ format; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 
 struct skeleton* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct skeleton *skel = vb2_get_drv_priv(vq);

	skel->field = skel->format.field;
	if (skel->field == V4L2_FIELD_ALTERNATE) {
		/*
		 * You cannot use read() with FIELD_ALTERNATE since the field
		 * information (TOP/BOTTOM) cannot be passed back to the user.
		 */
		if (vb2_fileio_is_active(vq))
			return -EINVAL;
		skel->field = V4L2_FIELD_TOP;
	}

	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	if (*nplanes)
		return sizes[0] < skel->format.sizeimage ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = skel->format.sizeimage;
	return 0;
}