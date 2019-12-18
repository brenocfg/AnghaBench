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
struct ins_operands {int dummy; } ;
struct ins {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* scnprintf ) (struct ins*,char*,size_t,struct ins_operands*,int) ;} ;

/* Variables and functions */
 int ins__raw_scnprintf (struct ins*,char*,size_t,struct ins_operands*,int) ; 
 int stub1 (struct ins*,char*,size_t,struct ins_operands*,int) ; 

int ins__scnprintf(struct ins *ins, char *bf, size_t size,
		   struct ins_operands *ops, int max_ins_name)
{
	if (ins->ops->scnprintf)
		return ins->ops->scnprintf(ins, bf, size, ops, max_ins_name);

	return ins__raw_scnprintf(ins, bf, size, ops, max_ins_name);
}