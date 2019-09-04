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
typedef  int /*<<< orphan*/  u64 ;
struct smb2_file_internal_info {int dummy; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_INTERNAL_INFORMATION ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILE ; 
 int query_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void**,int /*<<< orphan*/ *) ; 

int
SMB2_get_srv_num(const unsigned int xid, struct cifs_tcon *tcon,
		 u64 persistent_fid, u64 volatile_fid, __le64 *uniqueid)
{
	return query_info(xid, tcon, persistent_fid, volatile_fid,
			  FILE_INTERNAL_INFORMATION, SMB2_O_INFO_FILE, 0,
			  sizeof(struct smb2_file_internal_info),
			  sizeof(struct smb2_file_internal_info),
			  (void **)&uniqueid, NULL);
}