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
struct ceph_osd_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort_request (struct ceph_osd_request*,int) ; 

__attribute__((used)) static int abort_fn(struct ceph_osd_request *req, void *arg)
{
	int err = *(int *)arg;

	abort_request(req, err);
	return 0; /* continue iteration */
}