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
struct ceph_mount_options {struct ceph_mount_options* fscache_uniq; struct ceph_mount_options* server_path; struct ceph_mount_options* mds_namespace; struct ceph_mount_options* snapdir_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dout (char*,struct ceph_mount_options*) ; 
 int /*<<< orphan*/  kfree (struct ceph_mount_options*) ; 

__attribute__((used)) static void destroy_mount_options(struct ceph_mount_options *args)
{
	dout("destroy_mount_options %p\n", args);
	kfree(args->snapdir_name);
	kfree(args->mds_namespace);
	kfree(args->server_path);
	kfree(args->fscache_uniq);
	kfree(args);
}