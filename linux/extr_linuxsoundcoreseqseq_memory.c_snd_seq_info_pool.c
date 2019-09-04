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
struct snd_seq_pool {int /*<<< orphan*/  event_alloc_failures; int /*<<< orphan*/  event_alloc_success; int /*<<< orphan*/  max_used; int /*<<< orphan*/  counter; int /*<<< orphan*/  total_elements; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,char*,int /*<<< orphan*/ ) ; 

void snd_seq_info_pool(struct snd_info_buffer *buffer,
		       struct snd_seq_pool *pool, char *space)
{
	if (pool == NULL)
		return;
	snd_iprintf(buffer, "%sPool size          : %d\n", space, pool->total_elements);
	snd_iprintf(buffer, "%sCells in use       : %d\n", space, atomic_read(&pool->counter));
	snd_iprintf(buffer, "%sPeak cells in use  : %d\n", space, pool->max_used);
	snd_iprintf(buffer, "%sAlloc success      : %d\n", space, pool->event_alloc_success);
	snd_iprintf(buffer, "%sAlloc failures     : %d\n", space, pool->event_alloc_failures);
}