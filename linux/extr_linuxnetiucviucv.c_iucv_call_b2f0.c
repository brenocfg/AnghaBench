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
struct TYPE_2__ {int iprcode; } ;
union iucv_param {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int __iucv_call_b2f0 (int,union iucv_param*) ; 

__attribute__((used)) static inline int iucv_call_b2f0(int command, union iucv_param *parm)
{
	int ccode;

	ccode = __iucv_call_b2f0(command, parm);
	return ccode == 1 ? parm->ctrl.iprcode : ccode;
}