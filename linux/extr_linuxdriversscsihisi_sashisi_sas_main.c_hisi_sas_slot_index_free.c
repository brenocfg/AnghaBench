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
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_slot_index_clear (struct hisi_hba*,int) ; 

__attribute__((used)) static void hisi_sas_slot_index_free(struct hisi_hba *hisi_hba, int slot_idx)
{
	hisi_sas_slot_index_clear(hisi_hba, slot_idx);
}