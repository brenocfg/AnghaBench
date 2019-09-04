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
struct snd_seq_client_pool {int output_free; int /*<<< orphan*/  client; } ;
struct seq_oss_writeq {TYPE_1__* dp; } ;
struct TYPE_2__ {int /*<<< orphan*/  cseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_GET_CLIENT_POOL ; 
 int /*<<< orphan*/  snd_seq_oss_control (TYPE_1__*,int /*<<< orphan*/ ,struct snd_seq_client_pool*) ; 

int
snd_seq_oss_writeq_get_free_size(struct seq_oss_writeq *q)
{
	struct snd_seq_client_pool pool;
	pool.client = q->dp->cseq;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_GET_CLIENT_POOL, &pool);
	return pool.output_free;
}