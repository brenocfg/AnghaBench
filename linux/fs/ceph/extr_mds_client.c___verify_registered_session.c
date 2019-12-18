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
struct ceph_mds_session {size_t s_mds; } ;
struct ceph_mds_client {size_t max_sessions; struct ceph_mds_session** sessions; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int __verify_registered_session(struct ceph_mds_client *mdsc,
				       struct ceph_mds_session *s)
{
	if (s->s_mds >= mdsc->max_sessions ||
	    mdsc->sessions[s->s_mds] != s)
		return -ENOENT;
	return 0;
}