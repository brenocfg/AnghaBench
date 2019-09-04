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
struct smd_channel_info_word {int dummy; } ;
struct smd_channel_info {int dummy; } ;
struct qcom_smd_edge {int /*<<< orphan*/  dev; int /*<<< orphan*/  remote_pid; } ;
struct qcom_smd_channel {size_t fifo_size; struct qcom_smd_channel* name; void* rx_fifo; void* tx_fifo; void* info; void* info_word; int /*<<< orphan*/  state_change_event; int /*<<< orphan*/  fblockread_event; int /*<<< orphan*/  recv_lock; int /*<<< orphan*/  tx_lock; struct qcom_smd_edge* edge; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct qcom_smd_channel* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qcom_smd_channel*) ; 
 struct qcom_smd_channel* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct qcom_smd_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_channel_reset (struct qcom_smd_channel*) ; 
 void* qcom_smem_get (int /*<<< orphan*/ ,unsigned int,size_t*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qcom_smd_channel *qcom_smd_create_channel(struct qcom_smd_edge *edge,
							unsigned smem_info_item,
							unsigned smem_fifo_item,
							char *name)
{
	struct qcom_smd_channel *channel;
	size_t fifo_size;
	size_t info_size;
	void *fifo_base;
	void *info;
	int ret;

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return ERR_PTR(-ENOMEM);

	channel->edge = edge;
	channel->name = kstrdup(name, GFP_KERNEL);
	if (!channel->name) {
		ret = -ENOMEM;
		goto free_channel;
	}

	spin_lock_init(&channel->tx_lock);
	spin_lock_init(&channel->recv_lock);
	init_waitqueue_head(&channel->fblockread_event);
	init_waitqueue_head(&channel->state_change_event);

	info = qcom_smem_get(edge->remote_pid, smem_info_item, &info_size);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto free_name_and_channel;
	}

	/*
	 * Use the size of the item to figure out which channel info struct to
	 * use.
	 */
	if (info_size == 2 * sizeof(struct smd_channel_info_word)) {
		channel->info_word = info;
	} else if (info_size == 2 * sizeof(struct smd_channel_info)) {
		channel->info = info;
	} else {
		dev_err(&edge->dev,
			"channel info of size %zu not supported\n", info_size);
		ret = -EINVAL;
		goto free_name_and_channel;
	}

	fifo_base = qcom_smem_get(edge->remote_pid, smem_fifo_item, &fifo_size);
	if (IS_ERR(fifo_base)) {
		ret =  PTR_ERR(fifo_base);
		goto free_name_and_channel;
	}

	/* The channel consist of a rx and tx fifo of equal size */
	fifo_size /= 2;

	dev_dbg(&edge->dev, "new channel '%s' info-size: %zu fifo-size: %zu\n",
			  name, info_size, fifo_size);

	channel->tx_fifo = fifo_base;
	channel->rx_fifo = fifo_base + fifo_size;
	channel->fifo_size = fifo_size;

	qcom_smd_channel_reset(channel);

	return channel;

free_name_and_channel:
	kfree(channel->name);
free_channel:
	kfree(channel);

	return ERR_PTR(ret);
}