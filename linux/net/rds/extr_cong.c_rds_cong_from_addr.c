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
struct in6_addr {int dummy; } ;
struct rds_cong_map {unsigned long* m_page_addrs; int /*<<< orphan*/  m_conn_list; int /*<<< orphan*/  m_waitq; struct in6_addr m_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long RDS_CONG_MAP_PAGES ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rds_cong_map*) ; 
 struct rds_cong_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cong_lock ; 
 struct rds_cong_map* rds_cong_tree_walk (struct in6_addr const*,struct rds_cong_map*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_cong_map*,struct in6_addr const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct rds_cong_map *rds_cong_from_addr(const struct in6_addr *addr)
{
	struct rds_cong_map *map;
	struct rds_cong_map *ret = NULL;
	unsigned long zp;
	unsigned long i;
	unsigned long flags;

	map = kzalloc(sizeof(struct rds_cong_map), GFP_KERNEL);
	if (!map)
		return NULL;

	map->m_addr = *addr;
	init_waitqueue_head(&map->m_waitq);
	INIT_LIST_HEAD(&map->m_conn_list);

	for (i = 0; i < RDS_CONG_MAP_PAGES; i++) {
		zp = get_zeroed_page(GFP_KERNEL);
		if (zp == 0)
			goto out;
		map->m_page_addrs[i] = zp;
	}

	spin_lock_irqsave(&rds_cong_lock, flags);
	ret = rds_cong_tree_walk(addr, map);
	spin_unlock_irqrestore(&rds_cong_lock, flags);

	if (!ret) {
		ret = map;
		map = NULL;
	}

out:
	if (map) {
		for (i = 0; i < RDS_CONG_MAP_PAGES && map->m_page_addrs[i]; i++)
			free_page(map->m_page_addrs[i]);
		kfree(map);
	}

	rdsdebug("map %p for addr %pI6c\n", ret, addr);

	return ret;
}