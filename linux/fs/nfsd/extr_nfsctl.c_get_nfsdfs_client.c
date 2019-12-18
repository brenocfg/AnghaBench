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
struct nfsdfs_client {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfsdfs_client* __get_nfsdfs_client (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 

struct nfsdfs_client *get_nfsdfs_client(struct inode *inode)
{
	struct nfsdfs_client *nc;

	inode_lock_shared(inode);
	nc = __get_nfsdfs_client(inode);
	inode_unlock_shared(inode);
	return nc;
}