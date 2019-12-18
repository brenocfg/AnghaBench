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
struct ceph_osd_request_target {int /*<<< orphan*/  target_oloc; int /*<<< orphan*/  target_oid; int /*<<< orphan*/  base_oloc; int /*<<< orphan*/  base_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_oid_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_oloc_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void target_destroy(struct ceph_osd_request_target *t)
{
	ceph_oid_destroy(&t->base_oid);
	ceph_oloc_destroy(&t->base_oloc);
	ceph_oid_destroy(&t->target_oid);
	ceph_oloc_destroy(&t->target_oloc);
}