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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u64 ;
struct smb2_file_link_info {int /*<<< orphan*/  FileNameLength; scalar_t__ RootDirectory; scalar_t__ ReplaceIfExists; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FILE_LINK_INFORMATION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILE ; 
 int UniStrnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int send_set_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,unsigned int*) ; 

int
SMB2_set_hardlink(const unsigned int xid, struct cifs_tcon *tcon,
		  u64 persistent_fid, u64 volatile_fid, __le16 *target_file)
{
	struct smb2_file_link_info info;
	void **data;
	unsigned int size[2];
	int rc;
	int len = (2 * UniStrnlen((wchar_t *)target_file, PATH_MAX));

	data = kmalloc_array(2, sizeof(void *), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	info.ReplaceIfExists = 0; /* 1 = replace existing link with new */
			      /* 0 = fail if link already exists */
	info.RootDirectory = 0;  /* MBZ for network ops (why does spec say?) */
	info.FileNameLength = cpu_to_le32(len);

	data[0] = &info;
	size[0] = sizeof(struct smb2_file_link_info);

	data[1] = target_file;
	size[1] = len + 2 /* null */;

	rc = send_set_info(xid, tcon, persistent_fid, volatile_fid,
			current->tgid, FILE_LINK_INFORMATION, SMB2_O_INFO_FILE,
			0, 2, data, size);
	kfree(data);
	return rc;
}