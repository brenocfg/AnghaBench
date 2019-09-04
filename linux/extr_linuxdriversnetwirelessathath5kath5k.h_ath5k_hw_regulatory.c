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
struct ath_regulatory {int dummy; } ;
struct ath5k_hw {int dummy; } ;
struct TYPE_2__ {struct ath_regulatory regulatory; } ;

/* Variables and functions */
 TYPE_1__* ath5k_hw_common (struct ath5k_hw*) ; 

__attribute__((used)) static inline struct ath_regulatory *ath5k_hw_regulatory(struct ath5k_hw *ah)
{
	return &(ath5k_hw_common(ah)->regulatory);
}