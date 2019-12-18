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
struct ceph_connection {char* error_msg; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  in_banner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_BANNER ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_hello(struct ceph_connection *con)
{
	if (memcmp(con->in_banner, CEPH_BANNER, strlen(CEPH_BANNER))) {
		pr_err("connect to %s got bad banner\n",
		       ceph_pr_addr(&con->peer_addr));
		con->error_msg = "protocol error, bad banner";
		return -1;
	}
	return 0;
}