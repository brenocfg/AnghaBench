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
typedef  int u32 ;
struct hisi_hba {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_PORT_NUM_MA ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_wideport_bitmap_v1_hw(struct hisi_hba *hisi_hba, int port_id)
{
	int i, bitmap = 0;
	u32 phy_port_num_ma = hisi_sas_read32(hisi_hba, PHY_PORT_NUM_MA);

	for (i = 0; i < hisi_hba->n_phy; i++)
		if (((phy_port_num_ma >> (i * 4)) & 0xf) == port_id)
			bitmap |= 1 << i;

	return bitmap;
}