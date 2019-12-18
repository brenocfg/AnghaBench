#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_6__ {int value; int size; int type; scalar_t__ key; } ;
struct TYPE_5__ {struct TYPE_5__* inherit_cpu_p; TYPE_2__** consts; } ;
typedef  TYPE_1__ CPU_MODEL ;
typedef  TYPE_2__ CPU_CONST ;

/* Variables and functions */
 int CPU_CONST_NONE ; 
 int MASK (int) ; 

__attribute__((used)) static CPU_CONST *const_by_value(CPU_MODEL *cpu, int type, ut32 v) {
	CPU_CONST **clist, *citem;

	for (clist = cpu->consts; *clist; clist++) {
		for (citem = *clist; citem && citem->key; citem++) {
			if (citem->value == (MASK (citem->size * 8) & v)
			&& (type == CPU_CONST_NONE || type == citem->type)) {
				return citem;
			}
		}
	}
	if (cpu->inherit_cpu_p) {
		return const_by_value (cpu->inherit_cpu_p, type, v);
	}
	return NULL;
}