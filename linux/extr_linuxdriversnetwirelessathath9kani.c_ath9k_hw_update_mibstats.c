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
typedef  scalar_t__ u32 ;
struct ath_hw {int dummy; } ;
struct ath9k_mib_stats {int /*<<< orphan*/  beacons; int /*<<< orphan*/  fcs_bad; int /*<<< orphan*/  ackrcv_bad; int /*<<< orphan*/  rts_bad; int /*<<< orphan*/  rts_good; } ;

/* Variables and functions */
 scalar_t__ AR_ACK_FAIL ; 
 scalar_t__ AR_BEACON_CNT ; 
 scalar_t__ AR_FCS_FAIL ; 
 scalar_t__ AR_RTS_FAIL ; 
 scalar_t__ AR_RTS_OK ; 
 int /*<<< orphan*/  REG_READ_MULTI (struct ath_hw*,scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void ath9k_hw_update_mibstats(struct ath_hw *ah,
				     struct ath9k_mib_stats *stats)
{
	u32 addr[5] = {AR_RTS_OK, AR_RTS_FAIL, AR_ACK_FAIL,
		       AR_FCS_FAIL, AR_BEACON_CNT};
	u32 data[5];

	REG_READ_MULTI(ah, &addr[0], &data[0], 5);
	/* AR_RTS_OK */
	stats->rts_good += data[0];
	/* AR_RTS_FAIL */
	stats->rts_bad += data[1];
	/* AR_ACK_FAIL */
	stats->ackrcv_bad += data[2];
	/* AR_FCS_FAIL */
	stats->fcs_bad += data[3];
	/* AR_BEACON_CNT */
	stats->beacons += data[4];
}