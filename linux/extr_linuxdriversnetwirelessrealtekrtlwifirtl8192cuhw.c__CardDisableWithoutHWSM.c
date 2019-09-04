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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _DisableAnalog (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  _DisableGPIO (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _DisableRFAFEAndResetBB (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _ResetDigitalProcedure1 (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  _ResetDigitalProcedure2 (struct ieee80211_hw*) ; 

__attribute__((used)) static void _CardDisableWithoutHWSM(struct ieee80211_hw *hw)
{
	/*==== RF Off Sequence ==== */
	_DisableRFAFEAndResetBB(hw);
	/*  ==== Reset digital sequence   ====== */
	_ResetDigitalProcedure1(hw, true);
	/*  ==== Pull GPIO PIN to balance level and LED control ====== */
	_DisableGPIO(hw);
	/*  ==== Reset digital sequence   ====== */
	_ResetDigitalProcedure2(hw);
	/*  ==== Disable analog sequence === */
	_DisableAnalog(hw, true);
}