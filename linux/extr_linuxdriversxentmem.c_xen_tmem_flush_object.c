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
typedef  int /*<<< orphan*/  u32 ;
struct tmem_oid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMEM_FLUSH_OBJECT ; 
 int xen_tmem_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmem_oid,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_tmem_flush_object(u32 pool_id, struct tmem_oid oid)
{
	return xen_tmem_op(TMEM_FLUSH_OBJECT, pool_id, oid, 0, 0, 0, 0, 0);
}