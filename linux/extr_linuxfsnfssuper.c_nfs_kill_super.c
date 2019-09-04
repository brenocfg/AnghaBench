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
struct super_block {int /*<<< orphan*/  s_dev; } ;
struct nfs_server {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  free_anon_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_shutdown_super (struct super_block*) ; 
 int /*<<< orphan*/  nfs_free_server (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_fscache_release_super_cookie (struct super_block*) ; 

void nfs_kill_super(struct super_block *s)
{
	struct nfs_server *server = NFS_SB(s);
	dev_t dev = s->s_dev;

	generic_shutdown_super(s);

	nfs_fscache_release_super_cookie(s);

	nfs_free_server(server);
	free_anon_bdev(dev);
}