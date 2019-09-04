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
struct ath_common {scalar_t__ bssidmask; scalar_t__ macaddr; void* ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BSSMSKL ; 
 int /*<<< orphan*/  AR_BSSMSKU ; 
 int /*<<< orphan*/  AR_STA_ID0 ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_SADH_MASK ; 
 int REG_READ (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (void*,int /*<<< orphan*/ ,int) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int get_unaligned_le32 (scalar_t__) ; 

void ath_hw_setbssidmask(struct ath_common *common)
{
	void *ah = common->ah;
	u32 id1;

	REG_WRITE(ah, AR_STA_ID0, get_unaligned_le32(common->macaddr));
	id1 = REG_READ(ah, AR_STA_ID1) & ~AR_STA_ID1_SADH_MASK;
	id1 |= get_unaligned_le16(common->macaddr + 4);
	REG_WRITE(ah, AR_STA_ID1, id1);

	REG_WRITE(ah, AR_BSSMSKL, get_unaligned_le32(common->bssidmask));
	REG_WRITE(ah, AR_BSSMSKU, get_unaligned_le16(common->bssidmask + 4));
}