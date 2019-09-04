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
typedef  int u32 ;
struct tmem_pool_uuid {int /*<<< orphan*/  uuid_hi; int /*<<< orphan*/  uuid_lo; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * uuid; } ;
struct TYPE_4__ {TYPE_1__ new; } ;
struct tmem_op {TYPE_2__ u; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int HYPERVISOR_tmem_op (struct tmem_op*) ; 
 int /*<<< orphan*/  TMEM_NEW_POOL ; 
 int TMEM_POOL_PAGESIZE_SHIFT ; 
 int TMEM_SPEC_VERSION ; 
 int TMEM_VERSION_SHIFT ; 

__attribute__((used)) static int xen_tmem_new_pool(struct tmem_pool_uuid uuid,
				u32 flags, unsigned long pagesize)
{
	struct tmem_op op;
	int rc = 0, pageshift;

	for (pageshift = 0; pagesize != 1; pageshift++)
		pagesize >>= 1;
	flags |= (pageshift - 12) << TMEM_POOL_PAGESIZE_SHIFT;
	flags |= TMEM_SPEC_VERSION << TMEM_VERSION_SHIFT;
	op.cmd = TMEM_NEW_POOL;
	op.u.new.uuid[0] = uuid.uuid_lo;
	op.u.new.uuid[1] = uuid.uuid_hi;
	op.u.new.flags = flags;
	rc = HYPERVISOR_tmem_op(&op);
	return rc;
}