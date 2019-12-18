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
struct TYPE_2__ {int /*<<< orphan*/  stopping; } ;
struct ceph_client {int /*<<< orphan*/  options; TYPE_1__ msgr; int /*<<< orphan*/  monc; int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ceph_debugfs_client_cleanup (struct ceph_client*) ; 
 int /*<<< orphan*/  ceph_destroy_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_messenger_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  ceph_monc_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_osdc_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_client*) ; 
 int /*<<< orphan*/  kfree (struct ceph_client*) ; 

void ceph_destroy_client(struct ceph_client *client)
{
	dout("destroy_client %p\n", client);

	atomic_set(&client->msgr.stopping, 1);

	/* unmount */
	ceph_osdc_stop(&client->osdc);
	ceph_monc_stop(&client->monc);
	ceph_messenger_fini(&client->msgr);

	ceph_debugfs_client_cleanup(client);

	ceph_destroy_options(client->options);

	kfree(client);
	dout("destroy_client %p done\n", client);
}