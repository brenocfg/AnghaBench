#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  opcode64; TYPE_1__* insn; } ;
typedef  TYPE_2__ tms320_dasm_t ;
struct TYPE_8__ {scalar_t__ v; int /*<<< orphan*/  n; int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ insn_mask_t ;
struct TYPE_6__ {TYPE_3__* m_list; } ;

/* Variables and functions */
 scalar_t__ get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_list_last (TYPE_3__*) ; 

int run_m_list(tms320_dasm_t * dasm)
{
	insn_mask_t * mask;

	if (!dasm->insn->m_list) {
		return 1;
	}

	for (mask = dasm->insn->m_list; !m_list_last(mask); mask++) {
		/* match bits in range [f, f + n] with mask's value */
		if (get_bits (dasm->opcode64, mask->f, mask->n) != mask->v) {
			return 0;
		}
	}

	return 1;
}