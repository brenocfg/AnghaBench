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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_key_conf {int keyidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TKIP_PN_TO_IV16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TKIP_PN_TO_IV32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * write_tkip_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8 *ieee80211_tkip_add_iv(u8 *pos, struct ieee80211_key_conf *keyconf, u64 pn)
{
	pos = write_tkip_iv(pos, TKIP_PN_TO_IV16(pn));
	*pos++ = (keyconf->keyidx << 6) | (1 << 5) /* Ext IV */;
	put_unaligned_le32(TKIP_PN_TO_IV32(pn), pos);
	return pos + 4;
}