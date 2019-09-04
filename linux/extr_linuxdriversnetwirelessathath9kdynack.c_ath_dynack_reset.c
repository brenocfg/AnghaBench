#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ h_rb; scalar_t__ t_rb; } ;
struct TYPE_3__ {scalar_t__ h_rb; scalar_t__ t_rb; } ;
struct ath_dynack {int ackto; TYPE_2__ ack_rbf; TYPE_1__ st_rbf; int /*<<< orphan*/  lto; } ;
struct ath_hw {struct ath_dynack dynack; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_set_ack_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_cts_timeout (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_setslottime (struct ath_hw*,int) ; 
 int /*<<< orphan*/  jiffies ; 

void ath_dynack_reset(struct ath_hw *ah)
{
	/* ackto = slottime + sifs + air delay */
	u32 ackto = 9 + 16 + 64;
	struct ath_dynack *da = &ah->dynack;

	da->lto = jiffies;
	da->ackto = ackto;

	da->st_rbf.t_rb = 0;
	da->st_rbf.h_rb = 0;
	da->ack_rbf.t_rb = 0;
	da->ack_rbf.h_rb = 0;

	/* init acktimeout */
	ath9k_hw_setslottime(ah, (ackto - 3) / 2);
	ath9k_hw_set_ack_timeout(ah, ackto);
	ath9k_hw_set_cts_timeout(ah, ackto);
}