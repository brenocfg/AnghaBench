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
struct TYPE_2__ {int /*<<< orphan*/  ippathid; int /*<<< orphan*/  ipuser; } ;
union iucv_param {TYPE_1__ ctrl; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_SEVER ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 union iucv_param** iucv_param_irq ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 

__attribute__((used)) static int iucv_sever_pathid(u16 pathid, u8 *userdata)
{
	union iucv_param *parm;

	parm = iucv_param_irq[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	if (userdata)
		memcpy(parm->ctrl.ipuser, userdata, sizeof(parm->ctrl.ipuser));
	parm->ctrl.ippathid = pathid;
	return iucv_call_b2f0(IUCV_SEVER, parm);
}