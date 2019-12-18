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
struct ceph_mdsmap {int m_num_mds; struct ceph_mdsmap* m_data_pg_pools; struct ceph_mdsmap* m_info; struct ceph_mdsmap* export_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ceph_mdsmap*) ; 

void ceph_mdsmap_destroy(struct ceph_mdsmap *m)
{
	int i;

	for (i = 0; i < m->m_num_mds; i++)
		kfree(m->m_info[i].export_targets);
	kfree(m->m_info);
	kfree(m->m_data_pg_pools);
	kfree(m);
}