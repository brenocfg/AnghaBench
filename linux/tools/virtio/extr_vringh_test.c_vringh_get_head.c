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
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int num; TYPE_1__* avail; } ;
struct vringh {scalar_t__ last_avail_idx; TYPE_2__ vring; int /*<<< orphan*/  weak_barriers; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int get_user (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_rmb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vringh_get_head(struct vringh *vrh, u16 *head)
{
	u16 avail_idx, i;
	int err;

	err = get_user(avail_idx, &vrh->vring.avail->idx);
	if (err)
		return err;

	if (vrh->last_avail_idx == avail_idx)
		return 0;

	/* Only get avail ring entries after they have been exposed by guest. */
	virtio_rmb(vrh->weak_barriers);

	i = vrh->last_avail_idx & (vrh->vring.num - 1);

	err = get_user(*head, &vrh->vring.avail->ring[i]);
	if (err)
		return err;

	vrh->last_avail_idx++;
	return 1;
}