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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  start_phy_v1_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  stop_phy_v1_hw (struct hisi_hba*,int) ; 

__attribute__((used)) static void phy_hard_reset_v1_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	stop_phy_v1_hw(hisi_hba, phy_no);
	msleep(100);
	start_phy_v1_hw(hisi_hba, phy_no);
}