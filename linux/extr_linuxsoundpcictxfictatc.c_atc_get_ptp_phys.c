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
struct ct_atc {TYPE_1__* vm; } ;
struct TYPE_2__ {unsigned long (* get_ptp_phys ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 unsigned long stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static unsigned long atc_get_ptp_phys(struct ct_atc *atc, int index)
{
	return atc->vm->get_ptp_phys(atc->vm, index);
}