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
struct lb_stats {unsigned int tx_bytes; } ;
struct lb_priv {int /*<<< orphan*/  pcpu_stats; } ;
struct lb_port_priv {int /*<<< orphan*/  pcpu_stats; } ;
struct lb_pcpu_stats {int /*<<< orphan*/  syncp; struct lb_stats* hash_stats; } ;

/* Variables and functions */
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lb_update_tx_stats(unsigned int tx_bytes, struct lb_priv *lb_priv,
			       struct lb_port_priv *lb_port_priv,
			       unsigned char hash)
{
	struct lb_pcpu_stats *pcpu_stats;
	struct lb_stats *port_stats;
	struct lb_stats *hash_stats;

	pcpu_stats = this_cpu_ptr(lb_priv->pcpu_stats);
	port_stats = this_cpu_ptr(lb_port_priv->pcpu_stats);
	hash_stats = &pcpu_stats->hash_stats[hash];
	u64_stats_update_begin(&pcpu_stats->syncp);
	port_stats->tx_bytes += tx_bytes;
	hash_stats->tx_bytes += tx_bytes;
	u64_stats_update_end(&pcpu_stats->syncp);
}