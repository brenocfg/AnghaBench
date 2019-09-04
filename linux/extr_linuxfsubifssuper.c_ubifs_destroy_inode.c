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
struct ubifs_inode {int /*<<< orphan*/  data; } ;
struct inode {int /*<<< orphan*/  i_rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_i_callback ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 

__attribute__((used)) static void ubifs_destroy_inode(struct inode *inode)
{
	struct ubifs_inode *ui = ubifs_inode(inode);

	kfree(ui->data);
	call_rcu(&inode->i_rcu, ubifs_i_callback);
}