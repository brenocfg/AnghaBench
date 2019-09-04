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
struct ath_common {int dummy; } ;
struct ath5k_hw {struct ath_common common; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ath_common *ath5k_hw_common(struct ath5k_hw *ah)
{
	return &ah->common;
}