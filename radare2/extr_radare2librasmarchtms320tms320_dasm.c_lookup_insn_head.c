#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_6__ {int opcode; TYPE_2__* head; int /*<<< orphan*/ * insn; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ tms320_dasm_t ;
struct TYPE_7__ {int /*<<< orphan*/  insn; } ;
typedef  TYPE_2__ insn_head_t ;

/* Variables and functions */
 scalar_t__ TMS320_F_CPU_C55X ; 
 int* c55x_e_list ; 
 void* ht_up_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ tms320_f_get_cpu (TYPE_1__*) ; 

insn_head_t * lookup_insn_head(tms320_dasm_t * dasm) {
	ut8 * e_list = NULL;
	/* handle some exceptions */

	if (tms320_f_get_cpu (dasm) == TMS320_F_CPU_C55X) {
		e_list = c55x_e_list;
	}
	while (e_list && (e_list[0] && e_list[1])) {
		if ((dasm->opcode & e_list[0]) == e_list[1]) {
			dasm->head = ht_up_find (dasm->map, e_list[1], NULL);
			break;
		}
		e_list += 2;
	}
	if (!dasm->head) {
		dasm->head = ht_up_find (dasm->map, dasm->opcode, NULL);
		if (!dasm->head) {
			dasm->head = ht_up_find (dasm->map, (dasm->opcode & 0xfe), NULL);
		}
	}
	dasm->insn = dasm->head ? &dasm->head->insn : NULL;
	return dasm->head;
}