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
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/ * antCtrlChain; } ;

/* Variables and functions */
 TYPE_1__* ar9003_modal_header (struct ath_hw*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ar9003_hw_ant_ctrl_chain_get(struct ath_hw *ah, int chain,
					bool is2ghz)
{
	__le16 val = ar9003_modal_header(ah, is2ghz)->antCtrlChain[chain];
	return le16_to_cpu(val);
}