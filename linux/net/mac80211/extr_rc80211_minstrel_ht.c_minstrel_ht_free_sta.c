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
struct minstrel_ht_sta_priv {struct minstrel_ht_sta_priv* ratelist; struct minstrel_ht_sta_priv* sample_table; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct minstrel_ht_sta_priv*) ; 

__attribute__((used)) static void
minstrel_ht_free_sta(void *priv, struct ieee80211_sta *sta, void *priv_sta)
{
	struct minstrel_ht_sta_priv *msp = priv_sta;

	kfree(msp->sample_table);
	kfree(msp->ratelist);
	kfree(msp);
}