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
struct snd_seq_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_seq_pool*) ; 
 int /*<<< orphan*/  snd_seq_pool_done (struct snd_seq_pool*) ; 
 int /*<<< orphan*/  snd_seq_pool_mark_closing (struct snd_seq_pool*) ; 

int snd_seq_pool_delete(struct snd_seq_pool **ppool)
{
	struct snd_seq_pool *pool = *ppool;

	*ppool = NULL;
	if (pool == NULL)
		return 0;
	snd_seq_pool_mark_closing(pool);
	snd_seq_pool_done(pool);
	kfree(pool);
	return 0;
}