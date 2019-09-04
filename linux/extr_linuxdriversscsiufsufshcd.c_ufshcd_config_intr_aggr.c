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
typedef  int /*<<< orphan*/  u8 ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int INT_AGGR_COUNTER_THLD_VAL (int /*<<< orphan*/ ) ; 
 int INT_AGGR_ENABLE ; 
 int INT_AGGR_PARAM_WRITE ; 
 int INT_AGGR_TIMEOUT_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ufshcd_config_intr_aggr(struct ufs_hba *hba, u8 cnt, u8 tmout)
{
	ufshcd_writel(hba, INT_AGGR_ENABLE | INT_AGGR_PARAM_WRITE |
		      INT_AGGR_COUNTER_THLD_VAL(cnt) |
		      INT_AGGR_TIMEOUT_VAL(tmout),
		      REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL);
}