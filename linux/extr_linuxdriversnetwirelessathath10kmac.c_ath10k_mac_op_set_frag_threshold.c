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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int ath10k_mac_op_set_frag_threshold(struct ieee80211_hw *hw, u32 value)
{
	/* Even though there's a WMI enum for fragmentation threshold no known
	 * firmware actually implements it. Moreover it is not possible to rely
	 * frame fragmentation to mac80211 because firmware clears the "more
	 * fragments" bit in frame control making it impossible for remote
	 * devices to reassemble frames.
	 *
	 * Hence implement a dummy callback just to say fragmentation isn't
	 * supported. This effectively prevents mac80211 from doing frame
	 * fragmentation in software.
	 */
	return -EOPNOTSUPP;
}