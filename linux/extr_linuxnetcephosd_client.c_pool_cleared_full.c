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
struct ceph_pg_pool_info {scalar_t__ was_full; } ;
struct ceph_osd_client {int /*<<< orphan*/  osdmap; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  __pool_full (struct ceph_pg_pool_info*) ; 
 struct ceph_pg_pool_info* ceph_pg_pool_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pool_cleared_full(struct ceph_osd_client *osdc, s64 pool_id)
{
	struct ceph_pg_pool_info *pi;

	pi = ceph_pg_pool_by_id(osdc->osdmap, pool_id);
	if (!pi)
		return false;

	return pi->was_full && !__pool_full(pi);
}