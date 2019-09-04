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
struct TYPE_3__ {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  tlink; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_LOCKFLAG_UNLOCK ; 
 int SMB2_lock (unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb2_mand_lock(const unsigned int xid, struct cifsFileInfo *cfile, __u64 offset,
	       __u64 length, __u32 type, int lock, int unlock, bool wait)
{
	if (unlock && !lock)
		type = SMB2_LOCKFLAG_UNLOCK;
	return SMB2_lock(xid, tlink_tcon(cfile->tlink),
			 cfile->fid.persistent_fid, cfile->fid.volatile_fid,
			 current->tgid, length, offset, type, wait);
}