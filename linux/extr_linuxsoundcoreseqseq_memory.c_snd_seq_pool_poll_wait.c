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
struct snd_seq_pool {int /*<<< orphan*/  output_sleep; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_seq_output_ok (struct snd_seq_pool*) ; 

int snd_seq_pool_poll_wait(struct snd_seq_pool *pool, struct file *file,
			   poll_table *wait)
{
	poll_wait(file, &pool->output_sleep, wait);
	return snd_seq_output_ok(pool);
}