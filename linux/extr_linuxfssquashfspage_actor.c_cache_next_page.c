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
struct squashfs_page_actor {scalar_t__ next_page; scalar_t__ pages; void** buffer; } ;

/* Variables and functions */

__attribute__((used)) static void *cache_next_page(struct squashfs_page_actor *actor)
{
	if (actor->next_page == actor->pages)
		return NULL;

	return actor->buffer[actor->next_page++];
}