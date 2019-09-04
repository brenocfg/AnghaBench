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
struct ceph_osd_request_target {int size; int min_size; int /*<<< orphan*/  osd; int /*<<< orphan*/  up; int /*<<< orphan*/  acting; int /*<<< orphan*/  target_oloc; int /*<<< orphan*/  target_oid; int /*<<< orphan*/  base_oloc; int /*<<< orphan*/  base_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_HOMELESS_OSD ; 
 int /*<<< orphan*/  ceph_oid_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_oloc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_osds_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void target_init(struct ceph_osd_request_target *t)
{
	ceph_oid_init(&t->base_oid);
	ceph_oloc_init(&t->base_oloc);
	ceph_oid_init(&t->target_oid);
	ceph_oloc_init(&t->target_oloc);

	ceph_osds_init(&t->acting);
	ceph_osds_init(&t->up);
	t->size = -1;
	t->min_size = -1;

	t->osd = CEPH_HOMELESS_OSD;
}