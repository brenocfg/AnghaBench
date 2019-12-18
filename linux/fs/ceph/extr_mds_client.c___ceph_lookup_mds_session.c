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
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_client {int max_sessions; int /*<<< orphan*/ * sessions; } ;

/* Variables and functions */
 struct ceph_mds_session* get_session (int /*<<< orphan*/ ) ; 

struct ceph_mds_session *__ceph_lookup_mds_session(struct ceph_mds_client *mdsc,
						   int mds)
{
	if (mds >= mdsc->max_sessions || !mdsc->sessions[mds])
		return NULL;
	return get_session(mdsc->sessions[mds]);
}