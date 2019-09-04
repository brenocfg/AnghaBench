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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_tx_info {int dummy; } ;
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_txhdr_fw3 {int dummy; } ;

/* Variables and functions */
 int generate_txhdr_fw3 (struct b43legacy_wldev*,struct b43legacy_txhdr_fw3*,unsigned char const*,unsigned int,struct ieee80211_tx_info*,int /*<<< orphan*/ ) ; 

int b43legacy_generate_txhdr(struct b43legacy_wldev *dev,
			      u8 *txhdr,
			      const unsigned char *fragment_data,
			      unsigned int fragment_len,
			      struct ieee80211_tx_info *info,
			      u16 cookie)
{
	return generate_txhdr_fw3(dev, (struct b43legacy_txhdr_fw3 *)txhdr,
			   fragment_data, fragment_len,
			   info, cookie);
}