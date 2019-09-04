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
struct netfront_queue {unsigned int id; int /*<<< orphan*/  napi; struct netfront_info* info; } ;
struct netfront_info {TYPE_1__* xbdev; int /*<<< orphan*/  netdev; struct netfront_queue* queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct netfront_queue* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (int /*<<< orphan*/ ,unsigned int) ; 
 int xennet_init_queue (struct netfront_queue*) ; 
 int /*<<< orphan*/  xennet_poll ; 

__attribute__((used)) static int xennet_create_queues(struct netfront_info *info,
				unsigned int *num_queues)
{
	unsigned int i;
	int ret;

	info->queues = kcalloc(*num_queues, sizeof(struct netfront_queue),
			       GFP_KERNEL);
	if (!info->queues)
		return -ENOMEM;

	for (i = 0; i < *num_queues; i++) {
		struct netfront_queue *queue = &info->queues[i];

		queue->id = i;
		queue->info = info;

		ret = xennet_init_queue(queue);
		if (ret < 0) {
			dev_warn(&info->xbdev->dev,
				 "only created %d queues\n", i);
			*num_queues = i;
			break;
		}

		netif_napi_add(queue->info->netdev, &queue->napi,
			       xennet_poll, 64);
		if (netif_running(info->netdev))
			napi_enable(&queue->napi);
	}

	netif_set_real_num_tx_queues(info->netdev, *num_queues);

	if (*num_queues == 0) {
		dev_err(&info->xbdev->dev, "no queues\n");
		return -EINVAL;
	}
	return 0;
}