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
struct pppol2tp_ioc_stats {void* rx_errors; void* rx_oos_packets; void* rx_seq_discards; void* rx_bytes; void* rx_packets; void* tx_errors; void* tx_bytes; void* tx_packets; } ;
struct l2tp_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_oos_packets; int /*<<< orphan*/  rx_seq_discards; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;

/* Variables and functions */
 void* atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pppol2tp_ioc_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pppol2tp_copy_stats(struct pppol2tp_ioc_stats *dest,
				const struct l2tp_stats *stats)
{
	memset(dest, 0, sizeof(*dest));

	dest->tx_packets = atomic_long_read(&stats->tx_packets);
	dest->tx_bytes = atomic_long_read(&stats->tx_bytes);
	dest->tx_errors = atomic_long_read(&stats->tx_errors);
	dest->rx_packets = atomic_long_read(&stats->rx_packets);
	dest->rx_bytes = atomic_long_read(&stats->rx_bytes);
	dest->rx_seq_discards = atomic_long_read(&stats->rx_seq_discards);
	dest->rx_oos_packets = atomic_long_read(&stats->rx_oos_packets);
	dest->rx_errors = atomic_long_read(&stats->rx_errors);
}