#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct virtnet_info {unsigned int curr_queue_pairs; struct send_queue* sq; struct receive_queue* rq; } ;
struct TYPE_6__ {int /*<<< orphan*/  syncp; } ;
struct send_queue {TYPE_2__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  syncp; } ;
struct receive_queue {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_8__ {size_t offset; } ;
struct TYPE_7__ {size_t offset; } ;

/* Variables and functions */
 unsigned int VIRTNET_RQ_STATS_LEN ; 
 unsigned int VIRTNET_SQ_STATS_LEN ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_4__* virtnet_rq_stats_desc ; 
 TYPE_3__* virtnet_sq_stats_desc ; 

__attribute__((used)) static void virtnet_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct virtnet_info *vi = netdev_priv(dev);
	unsigned int idx = 0, start, i, j;
	const u8 *stats_base;
	size_t offset;

	for (i = 0; i < vi->curr_queue_pairs; i++) {
		struct receive_queue *rq = &vi->rq[i];

		stats_base = (u8 *)&rq->stats;
		do {
			start = u64_stats_fetch_begin_irq(&rq->stats.syncp);
			for (j = 0; j < VIRTNET_RQ_STATS_LEN; j++) {
				offset = virtnet_rq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			}
		} while (u64_stats_fetch_retry_irq(&rq->stats.syncp, start));
		idx += VIRTNET_RQ_STATS_LEN;
	}

	for (i = 0; i < vi->curr_queue_pairs; i++) {
		struct send_queue *sq = &vi->sq[i];

		stats_base = (u8 *)&sq->stats;
		do {
			start = u64_stats_fetch_begin_irq(&sq->stats.syncp);
			for (j = 0; j < VIRTNET_SQ_STATS_LEN; j++) {
				offset = virtnet_sq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			}
		} while (u64_stats_fetch_retry_irq(&sq->stats.syncp, start));
		idx += VIRTNET_SQ_STATS_LEN;
	}
}