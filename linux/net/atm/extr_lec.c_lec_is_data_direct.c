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
struct TYPE_8__ {TYPE_3__* blli; } ;
struct atm_vcc {TYPE_4__ sap; } ;
struct TYPE_5__ {scalar_t__* snap; } ;
struct TYPE_6__ {TYPE_1__ tr9577; } ;
struct TYPE_7__ {TYPE_2__ l3; } ;

/* Variables and functions */
 scalar_t__ LEC_DATA_DIRECT_8023 ; 
 scalar_t__ LEC_DATA_DIRECT_8025 ; 

__attribute__((used)) static int lec_is_data_direct(struct atm_vcc *vcc)
{
	return ((vcc->sap.blli[0].l3.tr9577.snap[4] == LEC_DATA_DIRECT_8023) ||
		(vcc->sap.blli[0].l3.tr9577.snap[4] == LEC_DATA_DIRECT_8025));
}