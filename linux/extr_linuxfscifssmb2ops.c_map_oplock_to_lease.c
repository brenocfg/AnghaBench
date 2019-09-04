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
typedef  scalar_t__ u8 ;
typedef  int __le32 ;

/* Variables and functions */
 int SMB2_LEASE_HANDLE_CACHING ; 
 int SMB2_LEASE_READ_CACHING ; 
 int SMB2_LEASE_WRITE_CACHING ; 
 scalar_t__ SMB2_OPLOCK_LEVEL_BATCH ; 
 scalar_t__ SMB2_OPLOCK_LEVEL_EXCLUSIVE ; 
 scalar_t__ SMB2_OPLOCK_LEVEL_II ; 

__attribute__((used)) static __le32
map_oplock_to_lease(u8 oplock)
{
	if (oplock == SMB2_OPLOCK_LEVEL_EXCLUSIVE)
		return SMB2_LEASE_WRITE_CACHING | SMB2_LEASE_READ_CACHING;
	else if (oplock == SMB2_OPLOCK_LEVEL_II)
		return SMB2_LEASE_READ_CACHING;
	else if (oplock == SMB2_OPLOCK_LEVEL_BATCH)
		return SMB2_LEASE_HANDLE_CACHING | SMB2_LEASE_READ_CACHING |
		       SMB2_LEASE_WRITE_CACHING;
	return 0;
}