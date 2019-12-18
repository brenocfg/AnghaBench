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
struct ceph_msgpool {int type; int front_len; int max_data_items; char const* name; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dout (char*,char const*) ; 
 int /*<<< orphan*/  mempool_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceph_msgpool*) ; 
 int /*<<< orphan*/  msgpool_alloc ; 
 int /*<<< orphan*/  msgpool_free ; 

int ceph_msgpool_init(struct ceph_msgpool *pool, int type,
		      int front_len, int max_data_items, int size,
		      const char *name)
{
	dout("msgpool %s init\n", name);
	pool->type = type;
	pool->front_len = front_len;
	pool->max_data_items = max_data_items;
	pool->pool = mempool_create(size, msgpool_alloc, msgpool_free, pool);
	if (!pool->pool)
		return -ENOMEM;
	pool->name = name;
	return 0;
}