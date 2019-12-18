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
struct snd_seq_client_pool {int output_room; int /*<<< orphan*/  client; } ;
struct seq_oss_writeq {TYPE_1__* dp; } ;
struct TYPE_2__ {int /*<<< orphan*/  cseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_GET_CLIENT_POOL ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_SET_CLIENT_POOL ; 
 int /*<<< orphan*/  snd_seq_oss_control (TYPE_1__*,int /*<<< orphan*/ ,struct snd_seq_client_pool*) ; 

void
snd_seq_oss_writeq_set_output(struct seq_oss_writeq *q, int val)
{
	struct snd_seq_client_pool pool;
	pool.client = q->dp->cseq;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_GET_CLIENT_POOL, &pool);
	pool.output_room = val;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_SET_CLIENT_POOL, &pool);
}