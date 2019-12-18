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
struct nfs4_ol_stateid {unsigned char st_deny_bmap; } ;

/* Variables and functions */
 int NFS4_SHARE_DENY_BOTH ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline void
set_deny(u32 deny, struct nfs4_ol_stateid *stp)
{
	unsigned char mask = 1 << deny;

	WARN_ON_ONCE(deny > NFS4_SHARE_DENY_BOTH);
	stp->st_deny_bmap |= mask;
}