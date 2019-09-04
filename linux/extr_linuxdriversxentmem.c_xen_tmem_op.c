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
typedef  void* u32 ;
struct TYPE_3__ {int /*<<< orphan*/  gmfn; void* len; void* pfn_offset; void* tmem_offset; void* index; int /*<<< orphan*/ * oid; } ;
struct TYPE_4__ {TYPE_1__ gen; } ;
struct tmem_op {TYPE_2__ u; void* pool_id; void* cmd; } ;
struct tmem_oid {int /*<<< orphan*/ * oid; } ;

/* Variables and functions */
 int HYPERVISOR_tmem_op (struct tmem_op*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int xen_tmem_op(u32 tmem_cmd, u32 tmem_pool, struct tmem_oid oid,
	u32 index, unsigned long gmfn, u32 tmem_offset, u32 pfn_offset, u32 len)
{
	struct tmem_op op;
	int rc = 0;

	op.cmd = tmem_cmd;
	op.pool_id = tmem_pool;
	op.u.gen.oid[0] = oid.oid[0];
	op.u.gen.oid[1] = oid.oid[1];
	op.u.gen.oid[2] = oid.oid[2];
	op.u.gen.index = index;
	op.u.gen.tmem_offset = tmem_offset;
	op.u.gen.pfn_offset = pfn_offset;
	op.u.gen.len = len;
	set_xen_guest_handle(op.u.gen.gmfn, (void *)gmfn);
	rc = HYPERVISOR_tmem_op(&op);
	return rc;
}