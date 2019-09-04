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

/* Variables and functions */
 int /*<<< orphan*/  PF_BRIDGE ; 
 int /*<<< orphan*/  RTM_DELMDB ; 
 int /*<<< orphan*/  RTM_GETMDB ; 
 int /*<<< orphan*/  RTM_NEWMDB ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * br_mdb_add ; 
 int /*<<< orphan*/ * br_mdb_del ; 
 int /*<<< orphan*/ * br_mdb_dump ; 
 int /*<<< orphan*/  rtnl_register_module (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void br_mdb_init(void)
{
	rtnl_register_module(THIS_MODULE, PF_BRIDGE, RTM_GETMDB, NULL, br_mdb_dump, 0);
	rtnl_register_module(THIS_MODULE, PF_BRIDGE, RTM_NEWMDB, br_mdb_add, NULL, 0);
	rtnl_register_module(THIS_MODULE, PF_BRIDGE, RTM_DELMDB, br_mdb_del, NULL, 0);
}