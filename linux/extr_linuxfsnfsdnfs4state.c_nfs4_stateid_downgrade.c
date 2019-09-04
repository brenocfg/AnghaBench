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
typedef  int u32 ;
struct nfs4_ol_stateid {int dummy; } ;

/* Variables and functions */
#define  NFS4_SHARE_ACCESS_BOTH 130 
#define  NFS4_SHARE_ACCESS_READ 129 
#define  NFS4_SHARE_ACCESS_WRITE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfs4_stateid_downgrade_bit (struct nfs4_ol_stateid*,int const) ; 

__attribute__((used)) static inline void nfs4_stateid_downgrade(struct nfs4_ol_stateid *stp, u32 to_access)
{
	switch (to_access) {
	case NFS4_SHARE_ACCESS_READ:
		nfs4_stateid_downgrade_bit(stp, NFS4_SHARE_ACCESS_WRITE);
		nfs4_stateid_downgrade_bit(stp, NFS4_SHARE_ACCESS_BOTH);
		break;
	case NFS4_SHARE_ACCESS_WRITE:
		nfs4_stateid_downgrade_bit(stp, NFS4_SHARE_ACCESS_READ);
		nfs4_stateid_downgrade_bit(stp, NFS4_SHARE_ACCESS_BOTH);
		break;
	case NFS4_SHARE_ACCESS_BOTH:
		break;
	default:
		WARN_ON_ONCE(1);
	}
}