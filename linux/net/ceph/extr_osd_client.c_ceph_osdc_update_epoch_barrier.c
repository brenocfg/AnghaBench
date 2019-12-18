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
typedef  scalar_t__ u32 ;
struct ceph_osd_client {scalar_t__ epoch_barrier; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_epoch_barrier (struct ceph_osd_client*,scalar_t__) ; 

void ceph_osdc_update_epoch_barrier(struct ceph_osd_client *osdc, u32 eb)
{
	down_read(&osdc->lock);
	if (unlikely(eb > osdc->epoch_barrier)) {
		up_read(&osdc->lock);
		down_write(&osdc->lock);
		update_epoch_barrier(osdc, eb);
		up_write(&osdc->lock);
	} else {
		up_read(&osdc->lock);
	}
}