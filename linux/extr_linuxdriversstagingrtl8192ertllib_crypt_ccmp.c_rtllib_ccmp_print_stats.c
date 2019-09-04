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
struct rtllib_ccmp_data {int /*<<< orphan*/  dot11RSNAStatsCCMPDecryptErrors; int /*<<< orphan*/  dot11RSNAStatsCCMPReplays; int /*<<< orphan*/  dot11RSNAStatsCCMPFormatErrors; int /*<<< orphan*/  rx_pn; int /*<<< orphan*/  tx_pn; int /*<<< orphan*/  key_set; int /*<<< orphan*/  key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtllib_ccmp_print_stats(struct seq_file *m, void *priv)
{
	struct rtllib_ccmp_data *ccmp = priv;

	seq_printf(m,
		   "key[%d] alg=CCMP key_set=%d tx_pn=%pM rx_pn=%pM format_errors=%d replays=%d decrypt_errors=%d\n",
		   ccmp->key_idx, ccmp->key_set,
		   ccmp->tx_pn, ccmp->rx_pn,
		   ccmp->dot11RSNAStatsCCMPFormatErrors,
		   ccmp->dot11RSNAStatsCCMPReplays,
		   ccmp->dot11RSNAStatsCCMPDecryptErrors);
}