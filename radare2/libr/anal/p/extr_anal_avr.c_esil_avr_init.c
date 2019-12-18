#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ round; } ;
struct TYPE_6__ {int /*<<< orphan*/  hook_reg_write; } ;
struct TYPE_7__ {TYPE_1__ cb; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_ESIL_OP_TYPE_CUSTOM ; 
 int /*<<< orphan*/  avr_custom_des ; 
 int /*<<< orphan*/  avr_custom_spm_page_erase ; 
 int /*<<< orphan*/  avr_custom_spm_page_fill ; 
 int /*<<< orphan*/  avr_custom_spm_page_write ; 
 TYPE_5__ desctx ; 
 int /*<<< orphan*/  esil_avr_hook_reg_write ; 
 int /*<<< orphan*/  r_anal_esil_set_op (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esil_avr_init(RAnalEsil *esil) {
	if (!esil) {
		return false;
	}
	desctx.round = 0;
	r_anal_esil_set_op (esil, "des", avr_custom_des, 0, 0, R_ANAL_ESIL_OP_TYPE_CUSTOM);		//better meta info plz
	r_anal_esil_set_op (esil, "SPM_PAGE_ERASE", avr_custom_spm_page_erase, 0, 0, R_ANAL_ESIL_OP_TYPE_CUSTOM);
	r_anal_esil_set_op (esil, "SPM_PAGE_FILL", avr_custom_spm_page_fill, 0, 0, R_ANAL_ESIL_OP_TYPE_CUSTOM);
	r_anal_esil_set_op (esil, "SPM_PAGE_WRITE", avr_custom_spm_page_write, 0, 0, R_ANAL_ESIL_OP_TYPE_CUSTOM);
	esil->cb.hook_reg_write = esil_avr_hook_reg_write;

	return true;
}