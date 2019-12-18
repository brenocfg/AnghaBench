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
struct nfsdfs_client {int /*<<< orphan*/  cl_release; int /*<<< orphan*/  cl_ref; } ;
struct inode {struct nfsdfs_client* i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_ncl(struct inode *inode)
{
	struct nfsdfs_client *ncl = inode->i_private;

	inode->i_private = NULL;
	kref_put(&ncl->cl_ref, ncl->cl_release);
}