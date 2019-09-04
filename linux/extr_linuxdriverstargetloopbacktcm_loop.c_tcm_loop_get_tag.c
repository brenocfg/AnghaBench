#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct se_portal_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tl_tpgt; } ;

/* Variables and functions */
 TYPE_1__* tl_tpg (struct se_portal_group*) ; 

__attribute__((used)) static u16 tcm_loop_get_tag(struct se_portal_group *se_tpg)
{
	/*
	 * This Tag is used when forming SCSI Name identifier in EVPD=1 0x83
	 * to represent the SCSI Target Port.
	 */
	return tl_tpg(se_tpg)->tl_tpgt;
}