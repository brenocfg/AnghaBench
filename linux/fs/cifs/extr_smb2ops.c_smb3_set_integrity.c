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
struct fsctl_set_integrity_information_req {scalar_t__ Reserved; scalar_t__ Flags; int /*<<< orphan*/  ChecksumAlgorithm; } ;
struct cifs_tcon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_TYPE_UNCHANGED ; 
 int /*<<< orphan*/  CIFSMaxBufSize ; 
 int /*<<< orphan*/  FSCTL_SET_INTEGRITY_INFORMATION ; 
 int SMB2_ioctl (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb3_set_integrity(const unsigned int xid, struct cifs_tcon *tcon,
		   struct cifsFileInfo *cfile)
{
	struct fsctl_set_integrity_information_req integr_info;
	unsigned int ret_data_len;

	integr_info.ChecksumAlgorithm = cpu_to_le16(CHECKSUM_TYPE_UNCHANGED);
	integr_info.Flags = 0;
	integr_info.Reserved = 0;

	return SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.volatile_fid,
			FSCTL_SET_INTEGRITY_INFORMATION,
			true /* is_fsctl */,
			(char *)&integr_info,
			sizeof(struct fsctl_set_integrity_information_req),
			CIFSMaxBufSize, NULL,
			&ret_data_len);

}