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
struct snd_util_memhdr {int /*<<< orphan*/  block_mutex; } ;
struct snd_util_memblk {int dummy; } ;

/* Variables and functions */
 struct snd_util_memblk* __snd_util_mem_alloc (struct snd_util_memhdr*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct snd_util_memblk *
snd_util_mem_alloc(struct snd_util_memhdr *hdr, int size)
{
	struct snd_util_memblk *blk;
	mutex_lock(&hdr->block_mutex);
	blk = __snd_util_mem_alloc(hdr, size);
	mutex_unlock(&hdr->block_mutex);
	return blk;
}