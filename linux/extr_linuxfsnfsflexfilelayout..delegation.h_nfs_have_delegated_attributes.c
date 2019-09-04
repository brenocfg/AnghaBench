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
struct inode {int dummy; } ;
struct TYPE_4__ {int cache_validity; } ;
struct TYPE_3__ {scalar_t__ (* have_delegation ) (struct inode*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int NFS_INO_REVAL_FORCED ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 scalar_t__ stub1 (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nfs_have_delegated_attributes(struct inode *inode)
{
	return NFS_PROTO(inode)->have_delegation(inode, FMODE_READ) &&
		!(NFS_I(inode)->cache_validity & NFS_INO_REVAL_FORCED);
}