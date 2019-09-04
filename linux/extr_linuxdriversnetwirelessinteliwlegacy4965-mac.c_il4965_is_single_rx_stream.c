#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ smps; scalar_t__ single_chain_sufficient; } ;
struct il_priv {TYPE_1__ current_ht_config; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_SMPS_STATIC ; 

__attribute__((used)) static bool
il4965_is_single_rx_stream(struct il_priv *il)
{
	return il->current_ht_config.smps == IEEE80211_SMPS_STATIC ||
	    il->current_ht_config.single_chain_sufficient;
}