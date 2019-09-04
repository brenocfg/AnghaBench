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
struct bfa_ioc_s {TYPE_1__* attr; } ;
struct TYPE_2__ {scalar_t__ brcd_serialnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_ADAPTER_SERIAL_NUM_LEN ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_ioc_get_adapter_serial_num(struct bfa_ioc_s *ioc, char *serial_num)
{
	memset((void *)serial_num, 0, BFA_ADAPTER_SERIAL_NUM_LEN);
	memcpy((void *)serial_num,
			(void *)ioc->attr->brcd_serialnum,
			BFA_ADAPTER_SERIAL_NUM_LEN);
}