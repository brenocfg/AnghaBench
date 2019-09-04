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
struct ieee80211_bss_conf {int aid; int /*<<< orphan*/  bssid; } ;
struct ar5523_cmd_set_associd {int /*<<< orphan*/  bssid; void* timoffset; void* associd; void* defaultrateix; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  associd ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WDCMSG_WRITE_ASSOCID ; 
 int ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,struct ar5523_cmd_set_associd*,int,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ar5523_cmd_set_associd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar5523_write_associd(struct ar5523 *ar,
				struct ieee80211_bss_conf *bss)
{
	struct ar5523_cmd_set_associd associd;

	memset(&associd, 0, sizeof(associd));
	associd.defaultrateix = cpu_to_be32(0);	/* XXX */
	associd.associd = cpu_to_be32(bss->aid);
	associd.timoffset = cpu_to_be32(0x3b);	/* XXX */
	memcpy(associd.bssid, bss->bssid, ETH_ALEN);
	return ar5523_cmd_write(ar, WDCMSG_WRITE_ASSOCID, &associd,
				sizeof(associd), 0);
}