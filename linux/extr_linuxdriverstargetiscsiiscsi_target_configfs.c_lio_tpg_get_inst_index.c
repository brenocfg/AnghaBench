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
typedef  int /*<<< orphan*/  u32 ;
struct se_portal_group {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tpg_tiqn; } ;
struct TYPE_3__ {int /*<<< orphan*/  tiqn_index; } ;

/* Variables and functions */
 TYPE_2__* iscsi_tpg (struct se_portal_group*) ; 

__attribute__((used)) static u32 lio_tpg_get_inst_index(struct se_portal_group *se_tpg)
{
	return iscsi_tpg(se_tpg)->tpg_tiqn->tiqn_index;
}