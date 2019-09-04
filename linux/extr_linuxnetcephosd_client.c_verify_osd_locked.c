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
struct ceph_osd_client {int /*<<< orphan*/  lock; } ;
struct ceph_osd {int /*<<< orphan*/  lock; struct ceph_osd_client* o_osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_is_wrlocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void verify_osd_locked(struct ceph_osd *osd)
{
	struct ceph_osd_client *osdc = osd->o_osdc;

	WARN_ON(!(mutex_is_locked(&osd->lock) &&
		  rwsem_is_locked(&osdc->lock)) &&
		!rwsem_is_wrlocked(&osdc->lock));
}