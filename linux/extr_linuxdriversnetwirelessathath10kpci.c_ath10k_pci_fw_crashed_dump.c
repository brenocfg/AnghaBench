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
struct ath10k_fw_crash_data {int /*<<< orphan*/  guid; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_crash_counter; } ;
struct ath10k {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  data_lock; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  guid ;

/* Variables and functions */
 int /*<<< orphan*/  UUID_STRING_LEN ; 
 int /*<<< orphan*/  ath10k_ce_dump_registers (struct ath10k*,struct ath10k_fw_crash_data*) ; 
 struct ath10k_fw_crash_data* ath10k_coredump_new (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,char*) ; 
 int /*<<< orphan*/  ath10k_pci_dump_memory (struct ath10k*,struct ath10k_fw_crash_data*) ; 
 int /*<<< orphan*/  ath10k_pci_dump_registers (struct ath10k*,struct ath10k_fw_crash_data*) ; 
 int /*<<< orphan*/  ath10k_print_driver_info (struct ath10k*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_pci_fw_crashed_dump(struct ath10k *ar)
{
	struct ath10k_fw_crash_data *crash_data;
	char guid[UUID_STRING_LEN + 1];

	spin_lock_bh(&ar->data_lock);

	ar->stats.fw_crash_counter++;

	crash_data = ath10k_coredump_new(ar);

	if (crash_data)
		scnprintf(guid, sizeof(guid), "%pUl", &crash_data->guid);
	else
		scnprintf(guid, sizeof(guid), "n/a");

	ath10k_err(ar, "firmware crashed! (guid %s)\n", guid);
	ath10k_print_driver_info(ar);
	ath10k_pci_dump_registers(ar, crash_data);
	ath10k_ce_dump_registers(ar, crash_data);
	ath10k_pci_dump_memory(ar, crash_data);

	spin_unlock_bh(&ar->data_lock);

	queue_work(ar->workqueue, &ar->restart_work);
}