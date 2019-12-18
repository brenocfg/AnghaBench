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
struct TYPE_2__ {int /*<<< orphan*/  peer_addr; } ;
struct ceph_mon_client {TYPE_1__ con; int /*<<< orphan*/  cur_mon; int /*<<< orphan*/  hunting; } ;

/* Variables and functions */
 int /*<<< orphan*/  __close_session (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  __open_session (struct ceph_mon_client*) ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reopen_session(struct ceph_mon_client *monc)
{
	if (!monc->hunting)
		pr_info("mon%d %s session lost, hunting for new mon\n",
		    monc->cur_mon, ceph_pr_addr(&monc->con.peer_addr));

	__close_session(monc);
	__open_session(monc);
}