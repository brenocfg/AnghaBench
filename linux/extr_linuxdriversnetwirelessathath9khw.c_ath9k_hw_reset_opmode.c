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
typedef  int u32 ;
struct ath_hw {int sta_id1_defaults; int /*<<< orphan*/  opmode; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DEF_ANTENNA ; 
 int /*<<< orphan*/  AR_ISR ; 
 int /*<<< orphan*/  AR_RSSI_THR ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_RTS_USE_DEF ; 
 int /*<<< orphan*/  AR_STA_ID1_SADH_MASK ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int INIT_RSSI_THR ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_operating_mode (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_hw_setbssidmask (struct ath_common*) ; 

__attribute__((used)) static void ath9k_hw_reset_opmode(struct ath_hw *ah,
				  u32 macStaId1, u32 saveDefAntenna)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_RMW(ah, AR_STA_ID1, macStaId1
		  | AR_STA_ID1_RTS_USE_DEF
		  | ah->sta_id1_defaults,
		  ~AR_STA_ID1_SADH_MASK);
	ath_hw_setbssidmask(common);
	REG_WRITE(ah, AR_DEF_ANTENNA, saveDefAntenna);
	ath9k_hw_write_associd(ah);
	REG_WRITE(ah, AR_ISR, ~0);
	REG_WRITE(ah, AR_RSSI_THR, INIT_RSSI_THR);

	REGWRITE_BUFFER_FLUSH(ah);

	ath9k_hw_set_operating_mode(ah, ah->opmode);
}