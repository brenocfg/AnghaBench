#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ceph_mdsmap {scalar_t__ m_num_laggy; int m_num_mds; TYPE_1__* m_info; scalar_t__ m_damaged; int /*<<< orphan*/  m_enabled; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_STATE_ACTIVE ; 

bool ceph_mdsmap_is_cluster_available(struct ceph_mdsmap *m)
{
	int i, nr_active = 0;
	if (!m->m_enabled)
		return false;
	if (m->m_damaged)
		return false;
	if (m->m_num_laggy > 0)
		return false;
	for (i = 0; i < m->m_num_mds; i++) {
		if (m->m_info[i].state == CEPH_MDS_STATE_ACTIVE)
			nr_active++;
	}
	return nr_active > 0;
}