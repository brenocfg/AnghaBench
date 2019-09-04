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
struct TYPE_2__ {int /*<<< orphan*/  stbc_cap; int /*<<< orphan*/  ldpc_cap; scalar_t__ ht_option; } ;
struct sta_info {int ldpc; int stbc; TYPE_1__ htpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDPC_HT_ENABLE_TX ; 
 int /*<<< orphan*/  STBC_HT_ENABLE_TX ; 
 scalar_t__ TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_ldpc_stbc_cap(struct sta_info *psta)
{
	if (psta->htpriv.ht_option) {
		if (TEST_FLAG(psta->htpriv.ldpc_cap, LDPC_HT_ENABLE_TX))
			psta->ldpc = 1;

		if (TEST_FLAG(psta->htpriv.stbc_cap, STBC_HT_ENABLE_TX))
			psta->stbc = 1;
	} else {
		psta->ldpc = 0;
		psta->stbc = 0;
	}
}