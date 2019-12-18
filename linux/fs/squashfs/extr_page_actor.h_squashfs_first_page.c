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
struct squashfs_page_actor {int next_page; void** page; } ;

/* Variables and functions */

__attribute__((used)) static inline void *squashfs_first_page(struct squashfs_page_actor *actor)
{
	actor->next_page = 1;
	return actor->page[0];
}