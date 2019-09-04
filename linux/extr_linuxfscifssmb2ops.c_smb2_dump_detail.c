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
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
smb2_dump_detail(void *buf, struct TCP_Server_Info *server)
{
#ifdef CONFIG_CIFS_DEBUG2
	struct smb2_sync_hdr *shdr = (struct smb2_sync_hdr *)buf;

	cifs_dbg(VFS, "Cmd: %d Err: 0x%x Flags: 0x%x Mid: %llu Pid: %d\n",
		 shdr->Command, shdr->Status, shdr->Flags, shdr->MessageId,
		 shdr->ProcessId);
	cifs_dbg(VFS, "smb buf %p len %u\n", buf,
		 server->ops->calc_smb_size(buf, server));
#endif
}