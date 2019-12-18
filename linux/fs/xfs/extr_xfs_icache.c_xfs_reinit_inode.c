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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xfs_mount {int /*<<< orphan*/  m_super; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_nlink; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int inode_init_always (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  inode_peek_iversion (struct inode*) ; 
 int /*<<< orphan*/  inode_set_iversion_queried (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_reinit_inode(
	struct xfs_mount	*mp,
	struct inode		*inode)
{
	int		error;
	uint32_t	nlink = inode->i_nlink;
	uint32_t	generation = inode->i_generation;
	uint64_t	version = inode_peek_iversion(inode);
	umode_t		mode = inode->i_mode;
	dev_t		dev = inode->i_rdev;

	error = inode_init_always(mp->m_super, inode);

	set_nlink(inode, nlink);
	inode->i_generation = generation;
	inode_set_iversion_queried(inode, version);
	inode->i_mode = mode;
	inode->i_rdev = dev;
	return error;
}