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
struct k_atm_aal_stats {int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx_err; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx_err; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_stats(struct seq_file *seq, const char *aal,
  const struct k_atm_aal_stats *stats)
{
	seq_printf(seq, "%s ( %d %d %d %d %d )", aal,
		   atomic_read(&stats->tx), atomic_read(&stats->tx_err),
		   atomic_read(&stats->rx), atomic_read(&stats->rx_err),
		   atomic_read(&stats->rx_drop));
}