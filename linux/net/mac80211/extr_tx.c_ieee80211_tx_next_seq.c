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
typedef  int u16 ;
struct sta_info {int* tid_seq; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int IEEE80211_SCTL_SEQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static __le16 ieee80211_tx_next_seq(struct sta_info *sta, int tid)
{
	u16 *seq = &sta->tid_seq[tid];
	__le16 ret = cpu_to_le16(*seq);

	/* Increase the sequence number. */
	*seq = (*seq + 0x10) & IEEE80211_SCTL_SEQ;

	return ret;
}