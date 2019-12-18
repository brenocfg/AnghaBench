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
struct yfs_xdr_YFSStoreStatus {void* group; void* owner; void* mtime_client; void* mode; void* mask; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AFS_SET_MODE ; 
 int S_IALLUGO ; 
 void* htonl (int) ; 
 void* u64_to_xdr (int /*<<< orphan*/ ) ; 
 int xdr_size (struct yfs_xdr_YFSStoreStatus*) ; 

__attribute__((used)) static __be32 *xdr_encode_YFSStoreStatus_mode(__be32 *bp, mode_t mode)
{
	struct yfs_xdr_YFSStoreStatus *x = (void *)bp;

	x->mask		= htonl(AFS_SET_MODE);
	x->mode		= htonl(mode & S_IALLUGO);
	x->mtime_client	= u64_to_xdr(0);
	x->owner	= u64_to_xdr(0);
	x->group	= u64_to_xdr(0);
	return bp + xdr_size(x);
}