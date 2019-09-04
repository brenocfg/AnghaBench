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
struct rds_info_iterator {scalar_t__ offset; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,unsigned long) ; 
 unsigned long min (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,unsigned long,void*,unsigned long) ; 

void rds_info_copy(struct rds_info_iterator *iter, void *data,
		   unsigned long bytes)
{
	unsigned long this;

	while (bytes) {
		if (!iter->addr)
			iter->addr = kmap_atomic(*iter->pages);

		this = min(bytes, PAGE_SIZE - iter->offset);

		rdsdebug("page %p addr %p offset %lu this %lu data %p "
			  "bytes %lu\n", *iter->pages, iter->addr,
			  iter->offset, this, data, bytes);

		memcpy(iter->addr + iter->offset, data, this);

		data += this;
		bytes -= this;
		iter->offset += this;

		if (iter->offset == PAGE_SIZE) {
			kunmap_atomic(iter->addr);
			iter->addr = NULL;
			iter->offset = 0;
			iter->pages++;
		}
	}
}