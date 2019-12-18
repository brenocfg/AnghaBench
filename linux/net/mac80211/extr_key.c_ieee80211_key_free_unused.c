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
struct ieee80211_key {scalar_t__ local; scalar_t__ sdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_key_free_common (struct ieee80211_key*) ; 

void ieee80211_key_free_unused(struct ieee80211_key *key)
{
	WARN_ON(key->sdata || key->local);
	ieee80211_key_free_common(key);
}