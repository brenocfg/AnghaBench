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
struct snd_seq_client_pool {int output_pool; int output_room; int /*<<< orphan*/  client; } ;
struct seq_oss_writeq {int maxlen; int /*<<< orphan*/  sync_sleep; scalar_t__ sync_time; scalar_t__ sync_event_put; int /*<<< orphan*/  sync_lock; struct seq_oss_devinfo* dp; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; } ;
typedef  int /*<<< orphan*/  pool ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_SET_CLIENT_POOL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct seq_oss_writeq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_seq_client_pool*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_oss_control (struct seq_oss_devinfo*,int /*<<< orphan*/ ,struct snd_seq_client_pool*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct seq_oss_writeq *
snd_seq_oss_writeq_new(struct seq_oss_devinfo *dp, int maxlen)
{
	struct seq_oss_writeq *q;
	struct snd_seq_client_pool pool;

	if ((q = kzalloc(sizeof(*q), GFP_KERNEL)) == NULL)
		return NULL;
	q->dp = dp;
	q->maxlen = maxlen;
	spin_lock_init(&q->sync_lock);
	q->sync_event_put = 0;
	q->sync_time = 0;
	init_waitqueue_head(&q->sync_sleep);

	memset(&pool, 0, sizeof(pool));
	pool.client = dp->cseq;
	pool.output_pool = maxlen;
	pool.output_room = maxlen / 2;

	snd_seq_oss_control(dp, SNDRV_SEQ_IOCTL_SET_CLIENT_POOL, &pool);

	return q;
}