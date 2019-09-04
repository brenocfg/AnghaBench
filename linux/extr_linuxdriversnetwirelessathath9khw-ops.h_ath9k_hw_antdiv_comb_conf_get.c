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
struct ath_hw_antcomb_conf {int dummy; } ;
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* antdiv_comb_conf_get ) (struct ath_hw*,struct ath_hw_antcomb_conf*) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*,struct ath_hw_antcomb_conf*) ; 

__attribute__((used)) static inline void ath9k_hw_antdiv_comb_conf_get(struct ath_hw *ah,
		struct ath_hw_antcomb_conf *antconf)
{
	ath9k_hw_ops(ah)->antdiv_comb_conf_get(ah, antconf);
}