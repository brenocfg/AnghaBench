#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEP_FUNC_ARG_INT ; 
 int /*<<< orphan*/  TEP_FUNC_ARG_LONG ; 
 int /*<<< orphan*/  TEP_FUNC_ARG_VOID ; 
 int /*<<< orphan*/  init_disassembler () ; 
 int /*<<< orphan*/  kvm_emulate_insn_handler ; 
 int /*<<< orphan*/  kvm_exit_handler ; 
 int /*<<< orphan*/  kvm_mmu_get_page_handler ; 
 int /*<<< orphan*/  kvm_mmu_print_role ; 
 int /*<<< orphan*/  kvm_nested_vmexit_handler ; 
 int /*<<< orphan*/  kvm_nested_vmexit_inject_handler ; 
 int /*<<< orphan*/  process_is_writable_pte ; 
 int /*<<< orphan*/  tep_register_event_handler (struct tep_handle*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tep_register_print_function (struct tep_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TEP_PLUGIN_LOADER(struct tep_handle *tep)
{
	init_disassembler();

	tep_register_event_handler(tep, -1, "kvm", "kvm_exit",
				   kvm_exit_handler, NULL);

	tep_register_event_handler(tep, -1, "kvm", "kvm_emulate_insn",
				   kvm_emulate_insn_handler, NULL);

	tep_register_event_handler(tep, -1, "kvm", "kvm_nested_vmexit",
				   kvm_nested_vmexit_handler, NULL);

	tep_register_event_handler(tep, -1, "kvm", "kvm_nested_vmexit_inject",
				   kvm_nested_vmexit_inject_handler, NULL);

	tep_register_event_handler(tep, -1, "kvmmmu", "kvm_mmu_get_page",
				   kvm_mmu_get_page_handler, NULL);

	tep_register_event_handler(tep, -1, "kvmmmu", "kvm_mmu_sync_page",
				   kvm_mmu_print_role, NULL);

	tep_register_event_handler(tep, -1,
				   "kvmmmu", "kvm_mmu_unsync_page",
				   kvm_mmu_print_role, NULL);

	tep_register_event_handler(tep, -1, "kvmmmu", "kvm_mmu_zap_page",
				   kvm_mmu_print_role, NULL);

	tep_register_event_handler(tep, -1, "kvmmmu",
			"kvm_mmu_prepare_zap_page", kvm_mmu_print_role,
			NULL);

	tep_register_print_function(tep,
				    process_is_writable_pte,
				    TEP_FUNC_ARG_INT,
				    "is_writable_pte",
				    TEP_FUNC_ARG_LONG,
				    TEP_FUNC_ARG_VOID);
	return 0;
}