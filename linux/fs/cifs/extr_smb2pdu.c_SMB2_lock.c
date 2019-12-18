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
struct smb2_lock_element {int /*<<< orphan*/  Flags; void* Length; void* Offset; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ const SMB2_LOCKFLAG_FAIL_IMMEDIATELY ; 
 scalar_t__ const SMB2_LOCKFLAG_UNLOCK ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__ const) ; 
 void* cpu_to_le64 (int /*<<< orphan*/  const) ; 
 int smb2_lockv (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__ const,int,struct smb2_lock_element*) ; 

int
SMB2_lock(const unsigned int xid, struct cifs_tcon *tcon,
	  const __u64 persist_fid, const __u64 volatile_fid, const __u32 pid,
	  const __u64 length, const __u64 offset, const __u32 lock_flags,
	  const bool wait)
{
	struct smb2_lock_element lock;

	lock.Offset = cpu_to_le64(offset);
	lock.Length = cpu_to_le64(length);
	lock.Flags = cpu_to_le32(lock_flags);
	if (!wait && lock_flags != SMB2_LOCKFLAG_UNLOCK)
		lock.Flags |= cpu_to_le32(SMB2_LOCKFLAG_FAIL_IMMEDIATELY);

	return smb2_lockv(xid, tcon, persist_fid, volatile_fid, pid, 1, &lock);
}