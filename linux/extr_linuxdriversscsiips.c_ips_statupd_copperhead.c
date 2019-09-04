#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* adapt; scalar_t__ io_addr; } ;
typedef  TYPE_3__ ips_ha_t ;
struct TYPE_6__ {int hw_status_tail; int hw_status_start; TYPE_1__* p_status_tail; TYPE_1__* p_status_start; TYPE_1__* p_status_end; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  IPS_STATUS ;

/* Variables and functions */
 scalar_t__ IPS_REG_SQTR ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static uint32_t
ips_statupd_copperhead(ips_ha_t * ha)
{
	METHOD_TRACE("ips_statupd_copperhead", 1);

	if (ha->adapt->p_status_tail != ha->adapt->p_status_end) {
		ha->adapt->p_status_tail++;
		ha->adapt->hw_status_tail += sizeof (IPS_STATUS);
	} else {
		ha->adapt->p_status_tail = ha->adapt->p_status_start;
		ha->adapt->hw_status_tail = ha->adapt->hw_status_start;
	}

	outl(ha->adapt->hw_status_tail,
	     ha->io_addr + IPS_REG_SQTR);

	return (ha->adapt->p_status_tail->value);
}