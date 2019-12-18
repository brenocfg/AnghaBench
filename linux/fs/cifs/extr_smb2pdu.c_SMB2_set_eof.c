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
typedef  int /*<<< orphan*/  u32 ;
struct smb2_file_eof_info {int /*<<< orphan*/  EndOfFile; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_END_OF_FILE_INFORMATION ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILE ; 
 int send_set_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,unsigned int*) ; 

int
SMB2_set_eof(const unsigned int xid, struct cifs_tcon *tcon, u64 persistent_fid,
	     u64 volatile_fid, u32 pid, __le64 *eof)
{
	struct smb2_file_eof_info info;
	void *data;
	unsigned int size;

	info.EndOfFile = *eof;

	data = &info;
	size = sizeof(struct smb2_file_eof_info);

	return send_set_info(xid, tcon, persistent_fid, volatile_fid,
			pid, FILE_END_OF_FILE_INFORMATION, SMB2_O_INFO_FILE,
			0, 1, &data, &size);
}