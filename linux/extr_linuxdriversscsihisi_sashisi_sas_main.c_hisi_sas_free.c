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
struct hisi_hba {scalar_t__ wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 

void hisi_sas_free(struct hisi_hba *hisi_hba)
{
	if (hisi_hba->wq)
		destroy_workqueue(hisi_hba->wq);
}