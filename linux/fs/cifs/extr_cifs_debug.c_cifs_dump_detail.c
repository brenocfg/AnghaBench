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
struct TYPE_3__ {int /*<<< orphan*/  CifsError; } ;
struct smb_hdr {int /*<<< orphan*/  Pid; int /*<<< orphan*/  Mid; int /*<<< orphan*/  Flags2; int /*<<< orphan*/  Flags; TYPE_1__ Status; int /*<<< orphan*/  Command; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* calc_smb_size ) (struct smb_hdr*,struct TCP_Server_Info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct smb_hdr*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (struct smb_hdr*,struct TCP_Server_Info*) ; 

void cifs_dump_detail(void *buf, struct TCP_Server_Info *server)
{
#ifdef CONFIG_CIFS_DEBUG2
	struct smb_hdr *smb = (struct smb_hdr *)buf;

	cifs_dbg(VFS, "Cmd: %d Err: 0x%x Flags: 0x%x Flgs2: 0x%x Mid: %d Pid: %d\n",
		 smb->Command, smb->Status.CifsError,
		 smb->Flags, smb->Flags2, smb->Mid, smb->Pid);
	cifs_dbg(VFS, "smb buf %p len %u\n", smb,
		 server->ops->calc_smb_size(smb, server));
#endif /* CONFIG_CIFS_DEBUG2 */
}