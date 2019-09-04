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
struct se_portal_group {int dummy; } ;
struct TYPE_3__ {int demo_mode_write_protect; } ;
struct TYPE_4__ {TYPE_1__ tpg_attrib; } ;

/* Variables and functions */
 TYPE_2__* iscsi_tpg (struct se_portal_group*) ; 

__attribute__((used)) static int lio_tpg_check_demo_mode_write_protect(
	struct se_portal_group *se_tpg)
{
	return iscsi_tpg(se_tpg)->tpg_attrib.demo_mode_write_protect;
}