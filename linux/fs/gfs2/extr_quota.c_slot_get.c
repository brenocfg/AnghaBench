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
struct gfs2_sbd {unsigned int sd_quota_slots; int /*<<< orphan*/  sd_bitmap_lock; int /*<<< orphan*/  sd_quota_bitmap; } ;
struct gfs2_quota_data {scalar_t__ qd_slot_count; unsigned int qd_slot; struct gfs2_sbd* qd_sbd; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slot_get(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_sbd;
	unsigned int bit;
	int error = 0;

	spin_lock(&sdp->sd_bitmap_lock);
	if (qd->qd_slot_count != 0)
		goto out;

	error = -ENOSPC;
	bit = find_first_zero_bit(sdp->sd_quota_bitmap, sdp->sd_quota_slots);
	if (bit < sdp->sd_quota_slots) {
		set_bit(bit, sdp->sd_quota_bitmap);
		qd->qd_slot = bit;
		error = 0;
out:
		qd->qd_slot_count++;
	}
	spin_unlock(&sdp->sd_bitmap_lock);

	return error;
}