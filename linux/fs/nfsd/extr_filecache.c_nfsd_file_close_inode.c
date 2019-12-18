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
struct inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSD_FILE_HASH_BITS ; 
 int /*<<< orphan*/  __nfsd_file_close_inode (struct inode*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispose ; 
 scalar_t__ hash_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_dispose_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_file_close_inode (struct inode*,unsigned int,int) ; 

__attribute__((used)) static void
nfsd_file_close_inode(struct inode *inode)
{
	unsigned int		hashval = (unsigned int)hash_long(inode->i_ino,
						NFSD_FILE_HASH_BITS);
	LIST_HEAD(dispose);

	__nfsd_file_close_inode(inode, hashval, &dispose);
	trace_nfsd_file_close_inode(inode, hashval, !list_empty(&dispose));
	nfsd_file_dispose_list(&dispose);
}