#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_3__* pool_ns; } ;
struct TYPE_6__ {int /*<<< orphan*/  seed; } ;
struct TYPE_5__ {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct ceph_osd_request_target {TYPE_4__ target_oloc; TYPE_2__ pgid; TYPE_1__ target_oid; } ;
struct ceph_hobject_id {int is_max; int /*<<< orphan*/  pool; scalar_t__ nspace_len; int /*<<< orphan*/ * nspace; int /*<<< orphan*/  hash; int /*<<< orphan*/  snapid; int /*<<< orphan*/  oid_len; int /*<<< orphan*/  oid; scalar_t__ key_len; int /*<<< orphan*/ * key; } ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/ * str; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  ceph_hoid_build_hash_cache (struct ceph_hobject_id*) ; 

__attribute__((used)) static void hoid_fill_from_target(struct ceph_hobject_id *hoid,
				  const struct ceph_osd_request_target *t)
{
	hoid->key = NULL;
	hoid->key_len = 0;
	hoid->oid = t->target_oid.name;
	hoid->oid_len = t->target_oid.name_len;
	hoid->snapid = CEPH_NOSNAP;
	hoid->hash = t->pgid.seed;
	hoid->is_max = false;
	if (t->target_oloc.pool_ns) {
		hoid->nspace = t->target_oloc.pool_ns->str;
		hoid->nspace_len = t->target_oloc.pool_ns->len;
	} else {
		hoid->nspace = NULL;
		hoid->nspace_len = 0;
	}
	hoid->pool = t->target_oloc.pool;
	ceph_hoid_build_hash_cache(hoid);
}