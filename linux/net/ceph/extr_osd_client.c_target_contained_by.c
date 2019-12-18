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
struct ceph_osd_request_target {int dummy; } ;
struct ceph_hobject_id {int dummy; } ;

/* Variables and functions */
 int hoid_compare (struct ceph_hobject_id*,struct ceph_hobject_id const*) ; 
 int /*<<< orphan*/  hoid_fill_from_target (struct ceph_hobject_id*,struct ceph_osd_request_target const*) ; 

__attribute__((used)) static bool target_contained_by(const struct ceph_osd_request_target *t,
				const struct ceph_hobject_id *begin,
				const struct ceph_hobject_id *end)
{
	struct ceph_hobject_id hoid;
	int cmp;

	hoid_fill_from_target(&hoid, t);
	cmp = hoid_compare(&hoid, begin);
	return !cmp || (cmp > 0 && hoid_compare(&hoid, end) < 0);
}