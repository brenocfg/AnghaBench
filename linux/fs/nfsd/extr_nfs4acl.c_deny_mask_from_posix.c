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

/* Variables and functions */
 unsigned short ACL_EXECUTE ; 
 unsigned short ACL_READ ; 
 unsigned short ACL_WRITE ; 
 int NFS4_ACE_DELETE_CHILD ; 
 int NFS4_ACL_DIR ; 
 int NFS4_EXECUTE_MODE ; 
 int NFS4_READ_MODE ; 
 int NFS4_WRITE_MODE ; 

__attribute__((used)) static u32
deny_mask_from_posix(unsigned short perm, u32 flags)
{
	u32 mask = 0;

	if (perm & ACL_READ)
		mask |= NFS4_READ_MODE;
	if (perm & ACL_WRITE)
		mask |= NFS4_WRITE_MODE;
	if ((perm & ACL_WRITE) && (flags & NFS4_ACL_DIR))
		mask |= NFS4_ACE_DELETE_CHILD;
	if (perm & ACL_EXECUTE)
		mask |= NFS4_EXECUTE_MODE;
	return mask;
}