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

/* Variables and functions */
 int DFS_CACHE_HTABLE_SIZE ; 
 unsigned int jhash (void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int cache_entry_hash(const void *data, int size)
{
	unsigned int h;

	h = jhash(data, size, 0);
	return h & (DFS_CACHE_HTABLE_SIZE - 1);
}