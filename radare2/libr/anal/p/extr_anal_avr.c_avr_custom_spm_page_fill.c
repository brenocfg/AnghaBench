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
typedef  int ut64 ;
struct TYPE_7__ {TYPE_1__* anal; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpu; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RAnalEsil ;
typedef  int /*<<< orphan*/  CPU_MODEL ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONST_PARAM ; 
 int MASK (int) ; 
 int /*<<< orphan*/  __esil_pop_argument (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  const_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int const_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_cpu_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_esil_mem_write (TYPE_2__*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static bool avr_custom_spm_page_fill(RAnalEsil *esil) {
	CPU_MODEL *cpu;
	ut64 addr, page_size_bits, i;
	ut8 r0, r1;

	// sanity check
	if (!esil || !esil->anal || !esil->anal->reg) {
		return false;
	}

	// get target address, r0, r1
	if (!__esil_pop_argument(esil, &addr)) {
		return false;
	}

	if (!__esil_pop_argument (esil, &i)) {
		return false;
	}
	r0 = i;

	if (!__esil_pop_argument (esil, &i)) {
		return false;
	}
	r1 = i;

	// get details about current MCU and fix input address
	cpu = get_cpu_model (esil->anal->cpu);
	page_size_bits = const_get_value (const_by_name (cpu, CPU_CONST_PARAM, "page_size"));

	// align and crop base address
	addr &= (MASK (page_size_bits) ^ 1);

	// perform write to temporary page
	//eprintf ("SPM_PAGE_FILL bytes (%02x, %02x) @ 0x%08" PFMT64x ".\n", r1, r0, addr);
	r_anal_esil_mem_write (esil, addr++, &r0, 1);
	r_anal_esil_mem_write (esil, addr++, &r1, 1);

	return true;
}