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
struct list_head {int dummy; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_mds; scalar_t__ s_num_cap_releases; int /*<<< orphan*/  s_cap_releases; int /*<<< orphan*/  s_cap_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_cap_releases(struct ceph_mds_session *session,
				struct list_head *target)
{
	lockdep_assert_held(&session->s_cap_lock);

	list_splice_init(&session->s_cap_releases, target);
	session->s_num_cap_releases = 0;
	dout("dispose_cap_releases mds%d\n", session->s_mds);
}