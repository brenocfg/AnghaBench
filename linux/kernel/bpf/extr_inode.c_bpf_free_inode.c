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
struct inode {int /*<<< orphan*/  i_private; int /*<<< orphan*/  i_link; int /*<<< orphan*/  i_mode; } ;
typedef  enum bpf_type { ____Placeholder_bpf_type } bpf_type ;

/* Variables and functions */
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_any_put (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bpf_inode_type (struct inode*,int*) ; 
 int /*<<< orphan*/  free_inode_nonrcu (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_free_inode(struct inode *inode)
{
	enum bpf_type type;

	if (S_ISLNK(inode->i_mode))
		kfree(inode->i_link);
	if (!bpf_inode_type(inode, &type))
		bpf_any_put(inode->i_private, type);
	free_inode_nonrcu(inode);
}