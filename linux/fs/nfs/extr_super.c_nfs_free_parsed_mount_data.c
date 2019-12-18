#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct nfs_parsed_mount_data* hostname; struct nfs_parsed_mount_data* export_path; } ;
struct TYPE_3__ {struct nfs_parsed_mount_data* hostname; } ;
struct nfs_parsed_mount_data {int /*<<< orphan*/  lsm_opts; struct nfs_parsed_mount_data* fscache_uniq; TYPE_2__ nfs_server; TYPE_1__ mount_server; struct nfs_parsed_mount_data* client_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs_parsed_mount_data*) ; 
 int /*<<< orphan*/  security_free_mnt_opts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_free_parsed_mount_data(struct nfs_parsed_mount_data *data)
{
	if (data) {
		kfree(data->client_address);
		kfree(data->mount_server.hostname);
		kfree(data->nfs_server.export_path);
		kfree(data->nfs_server.hostname);
		kfree(data->fscache_uniq);
		security_free_mnt_opts(&data->lsm_opts);
		kfree(data);
	}
}