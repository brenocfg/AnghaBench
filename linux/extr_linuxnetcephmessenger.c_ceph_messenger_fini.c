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
struct ceph_messenger {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

void ceph_messenger_fini(struct ceph_messenger *msgr)
{
	put_net(read_pnet(&msgr->net));
}