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
typedef  int /*<<< orphan*/  u64 ;
struct smb2_file_full_ea_info {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_FULL_EA_INFORMATION ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILE ; 
 TYPE_1__* current ; 
 int send_set_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,int*) ; 

int
SMB2_set_ea(const unsigned int xid, struct cifs_tcon *tcon,
	    u64 persistent_fid, u64 volatile_fid,
	    struct smb2_file_full_ea_info *buf, int len)
{
	return send_set_info(xid, tcon, persistent_fid, volatile_fid,
		current->tgid, FILE_FULL_EA_INFORMATION, SMB2_O_INFO_FILE,
		0, 1, (void **)&buf, &len);
}