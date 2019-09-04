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
struct ceph_pg_mapping {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 struct ceph_pg_mapping* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_pg_mapping *alloc_pg_mapping(size_t payload_len)
{
	struct ceph_pg_mapping *pg;

	pg = kmalloc(sizeof(*pg) + payload_len, GFP_NOIO);
	if (!pg)
		return NULL;

	RB_CLEAR_NODE(&pg->node);
	return pg;
}