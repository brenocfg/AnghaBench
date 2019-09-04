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
struct ieee80211_bss_conf {int dummy; } ;
struct ar5523_cmd_rateset {int dummy; } ;
struct ar5523_cmd_rates {int /*<<< orphan*/  rateset; void* size; void* connid; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  rates ;

/* Variables and functions */
 int /*<<< orphan*/  WDCMSG_SET_BASIC_RATE ; 
 int ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,struct ar5523_cmd_rates*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_create_rateset (struct ar5523*,struct ieee80211_bss_conf*,int /*<<< orphan*/ *,int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct ar5523_cmd_rates*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar5523_set_basic_rates(struct ar5523 *ar,
				  struct ieee80211_bss_conf *bss)
{
	struct ar5523_cmd_rates rates;

	memset(&rates, 0, sizeof(rates));
	rates.connid = cpu_to_be32(2);		/* XXX */
	rates.size   = cpu_to_be32(sizeof(struct ar5523_cmd_rateset));
	ar5523_create_rateset(ar, bss, &rates.rateset, true);

	return ar5523_cmd_write(ar, WDCMSG_SET_BASIC_RATE, &rates,
				sizeof(rates), 0);
}