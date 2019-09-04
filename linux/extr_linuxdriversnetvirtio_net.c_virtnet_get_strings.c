#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct virtnet_info {unsigned int curr_queue_pairs; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {char* desc; } ;
struct TYPE_3__ {char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 unsigned int VIRTNET_RQ_STATS_LEN ; 
 unsigned int VIRTNET_SQ_STATS_LEN ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 TYPE_2__* virtnet_rq_stats_desc ; 
 TYPE_1__* virtnet_sq_stats_desc ; 

__attribute__((used)) static void virtnet_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
	struct virtnet_info *vi = netdev_priv(dev);
	char *p = (char *)data;
	unsigned int i, j;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < vi->curr_queue_pairs; i++) {
			for (j = 0; j < VIRTNET_RQ_STATS_LEN; j++) {
				snprintf(p, ETH_GSTRING_LEN, "rx_queue_%u_%s",
					 i, virtnet_rq_stats_desc[j].desc);
				p += ETH_GSTRING_LEN;
			}
		}

		for (i = 0; i < vi->curr_queue_pairs; i++) {
			for (j = 0; j < VIRTNET_SQ_STATS_LEN; j++) {
				snprintf(p, ETH_GSTRING_LEN, "tx_queue_%u_%s",
					 i, virtnet_sq_stats_desc[j].desc);
				p += ETH_GSTRING_LEN;
			}
		}
		break;
	}
}