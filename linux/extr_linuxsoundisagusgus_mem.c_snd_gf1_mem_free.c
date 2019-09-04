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
struct snd_gf1_mem_block {int dummy; } ;
struct snd_gf1_mem {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_gf1_mem_lock (struct snd_gf1_mem*,int) ; 
 struct snd_gf1_mem_block* snd_gf1_mem_look (struct snd_gf1_mem*,unsigned int) ; 
 int snd_gf1_mem_xfree (struct snd_gf1_mem*,struct snd_gf1_mem_block*) ; 

int snd_gf1_mem_free(struct snd_gf1_mem * alloc, unsigned int address)
{
	int result;
	struct snd_gf1_mem_block *block;

	snd_gf1_mem_lock(alloc, 0);
	if ((block = snd_gf1_mem_look(alloc, address)) != NULL) {
		result = snd_gf1_mem_xfree(alloc, block);
		snd_gf1_mem_lock(alloc, 1);
		return result;
	}
	snd_gf1_mem_lock(alloc, 1);
	return -EINVAL;
}