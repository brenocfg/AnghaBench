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
typedef  int u8 ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int /*<<< orphan*/  curbssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAX_PATTERN_MASK_SIZE ; 
 int MAX_PATTERN_SIZE ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_wow_apply_pattern (struct ath_hw*,int*,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath9k_wow_add_disassoc_deauth_pattern(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	int pattern_count = 0;
	int ret, i, byte_cnt = 0;
	u8 dis_deauth_pattern[MAX_PATTERN_SIZE];
	u8 dis_deauth_mask[MAX_PATTERN_SIZE];

	memset(dis_deauth_pattern, 0, MAX_PATTERN_SIZE);
	memset(dis_deauth_mask, 0, MAX_PATTERN_SIZE);

	/*
	 * Create Dissassociate / Deauthenticate packet filter
	 *
	 *     2 bytes        2 byte    6 bytes   6 bytes  6 bytes
	 *  +--------------+----------+---------+--------+--------+----
	 *  + Frame Control+ Duration +   DA    +  SA    +  BSSID +
	 *  +--------------+----------+---------+--------+--------+----
	 *
	 * The above is the management frame format for disassociate/
	 * deauthenticate pattern, from this we need to match the first byte
	 * of 'Frame Control' and DA, SA, and BSSID fields
	 * (skipping 2nd byte of FC and Duration feild.
	 *
	 * Disassociate pattern
	 * --------------------
	 * Frame control = 00 00 1010
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattern will be A0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 *
	 * Deauthenticate pattern
	 * ----------------------
	 * Frame control = 00 00 1100
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattern will be C0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 */

	/* Fill out the mask with all FF's */
	for (i = 0; i < MAX_PATTERN_MASK_SIZE; i++)
		dis_deauth_mask[i] = 0xff;

	/* copy the first byte of frame control field */
	dis_deauth_pattern[byte_cnt] = 0xa0;
	byte_cnt++;

	/* skip 2nd byte of frame control and Duration field */
	byte_cnt += 3;

	/*
	 * need not match the destination mac address, it can be a broadcast
	 * mac address or an unicast to this station
	 */
	byte_cnt += 6;

	/* copy the source mac address */
	memcpy((dis_deauth_pattern + byte_cnt), common->curbssid, ETH_ALEN);

	byte_cnt += 6;

	/* copy the bssid, its same as the source mac address */
	memcpy((dis_deauth_pattern + byte_cnt), common->curbssid, ETH_ALEN);

	/* Create Disassociate pattern mask */
	dis_deauth_mask[0] = 0xfe;
	dis_deauth_mask[1] = 0x03;
	dis_deauth_mask[2] = 0xc0;

	ret = ath9k_hw_wow_apply_pattern(ah, dis_deauth_pattern, dis_deauth_mask,
					 pattern_count, byte_cnt);
	if (ret)
		goto exit;

	pattern_count++;
	/*
	 * for de-authenticate pattern, only the first byte of the frame
	 * control field gets changed from 0xA0 to 0xC0
	 */
	dis_deauth_pattern[0] = 0xC0;

	ret = ath9k_hw_wow_apply_pattern(ah, dis_deauth_pattern, dis_deauth_mask,
					 pattern_count, byte_cnt);
exit:
	return ret;
}