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
typedef  int /*<<< orphan*/  u8 ;
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct hisi_hba {TYPE_1__* hw; } ;
struct TYPE_2__ {int (* write_gpio ) (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_write_gpio(struct sas_ha_struct *sha, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *write_data)
{
	struct hisi_hba *hisi_hba = sha->lldd_ha;

	if (!hisi_hba->hw->write_gpio)
		return -EOPNOTSUPP;

	return hisi_hba->hw->write_gpio(hisi_hba, reg_type,
				reg_index, reg_count, write_data);
}