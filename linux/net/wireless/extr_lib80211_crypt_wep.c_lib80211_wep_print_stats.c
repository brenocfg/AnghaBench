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
struct seq_file {int dummy; } ;
struct lib80211_wep_data {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lib80211_wep_print_stats(struct seq_file *m, void *priv)
{
	struct lib80211_wep_data *wep = priv;
	seq_printf(m, "key[%d] alg=WEP len=%d\n", wep->key_idx, wep->key_len);
}