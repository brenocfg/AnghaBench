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
typedef  int u16 ;
struct vringh_kiov {int dummy; } ;
struct TYPE_2__ {int num; } ;
struct vringh {TYPE_1__ vring; int /*<<< orphan*/  last_avail_idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __vringh_get_head (struct vringh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __vringh_iov (struct vringh*,int,struct vringh_kiov*,struct vringh_kiov*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copydesc_kern ; 
 int /*<<< orphan*/  getu16_kern ; 
 int /*<<< orphan*/  no_range_check ; 

int vringh_getdesc_kern(struct vringh *vrh,
			struct vringh_kiov *riov,
			struct vringh_kiov *wiov,
			u16 *head,
			gfp_t gfp)
{
	int err;

	err = __vringh_get_head(vrh, getu16_kern, &vrh->last_avail_idx);
	if (err < 0)
		return err;

	/* Empty... */
	if (err == vrh->vring.num)
		return 0;

	*head = err;
	err = __vringh_iov(vrh, *head, riov, wiov, no_range_check, NULL,
			   gfp, copydesc_kern);
	if (err)
		return err;

	return 1;
}