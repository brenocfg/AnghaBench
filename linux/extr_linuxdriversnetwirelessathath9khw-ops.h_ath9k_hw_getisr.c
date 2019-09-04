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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
typedef  enum ath9k_int { ____Placeholder_ath9k_int } ath9k_int ;
struct TYPE_2__ {int (* get_isr ) (struct ath_hw*,int*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_ops (struct ath_hw*) ; 
 int stub1 (struct ath_hw*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ath9k_hw_getisr(struct ath_hw *ah, enum ath9k_int *masked,
				   u32 *sync_cause_p)
{
	return ath9k_hw_ops(ah)->get_isr(ah, masked, sync_cause_p);
}