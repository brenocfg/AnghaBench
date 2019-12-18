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
struct compress_ioctl {int /*<<< orphan*/  CompressionState; } ;
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSMaxBufSize ; 
 int /*<<< orphan*/  COMPRESSION_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  FSCTL_SET_COMPRESSION ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_ioctl (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

int
SMB2_set_compression(const unsigned int xid, struct cifs_tcon *tcon,
		     u64 persistent_fid, u64 volatile_fid)
{
	int rc;
	struct  compress_ioctl fsctl_input;
	char *ret_data = NULL;

	fsctl_input.CompressionState =
			cpu_to_le16(COMPRESSION_FORMAT_DEFAULT);

	rc = SMB2_ioctl(xid, tcon, persistent_fid, volatile_fid,
			FSCTL_SET_COMPRESSION, true /* is_fsctl */,
			(char *)&fsctl_input /* data input */,
			2 /* in data len */, CIFSMaxBufSize /* max out data */,
			&ret_data /* out data */, NULL);

	cifs_dbg(FYI, "set compression rc %d\n", rc);

	return rc;
}