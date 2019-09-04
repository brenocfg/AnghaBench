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
struct request_sock {int /*<<< orphan*/  secid; } ;
struct flowi {int /*<<< orphan*/  flowi_secid; } ;

/* Variables and functions */

__attribute__((used)) static void selinux_req_classify_flow(const struct request_sock *req,
				      struct flowi *fl)
{
	fl->flowi_secid = req->secid;
}