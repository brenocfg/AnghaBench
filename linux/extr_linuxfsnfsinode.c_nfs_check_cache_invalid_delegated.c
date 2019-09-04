#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_validity; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 unsigned long NFS_INO_REVAL_FORCED ; 
 unsigned long NFS_INO_REVAL_PAGECACHE ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfs_check_cache_invalid_delegated(struct inode *inode, unsigned long flags)
{
	unsigned long cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);

	/* Special case for the pagecache or access cache */
	if (flags == NFS_INO_REVAL_PAGECACHE &&
	    !(cache_validity & NFS_INO_REVAL_FORCED))
		return false;
	return (cache_validity & flags) != 0;
}