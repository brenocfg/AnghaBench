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
struct ceph_fs_client {int /*<<< orphan*/  client; int /*<<< orphan*/  mount_options; int /*<<< orphan*/  wb_pagevec_pool; int /*<<< orphan*/  trunc_wq; int /*<<< orphan*/  pg_inv_wq; int /*<<< orphan*/  wb_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_destroy_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_mount_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_fs_client*) ; 
 int /*<<< orphan*/  kfree (struct ceph_fs_client*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_fs_client(struct ceph_fs_client *fsc)
{
	dout("destroy_fs_client %p\n", fsc);

	destroy_workqueue(fsc->wb_wq);
	destroy_workqueue(fsc->pg_inv_wq);
	destroy_workqueue(fsc->trunc_wq);

	mempool_destroy(fsc->wb_pagevec_pool);

	destroy_mount_options(fsc->mount_options);

	ceph_destroy_client(fsc->client);

	kfree(fsc);
	dout("destroy_fs_client %p done\n", fsc);
}