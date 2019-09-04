#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int* Protocol; char Command; int Flags; char WordCount; int /*<<< orphan*/  Flags2; int /*<<< orphan*/  Mid; int /*<<< orphan*/  Uid; int /*<<< orphan*/  Tid; void* PidHigh; void* Pid; int /*<<< orphan*/  smb_buf_length; } ;
struct cifs_tcon {int Flags; TYPE_1__* ses; scalar_t__ nocase; int /*<<< orphan*/  tid; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {int tgid; } ;
struct TYPE_5__ {scalar_t__ sign; } ;
struct TYPE_4__ {int capabilities; TYPE_2__* server; int /*<<< orphan*/  Suid; } ;

/* Variables and functions */
 int CAP_STATUS32 ; 
 int CAP_UNICODE ; 
 int /*<<< orphan*/  SMBFLG2_DFS ; 
 int /*<<< orphan*/  SMBFLG2_ERR_STATUS ; 
 int /*<<< orphan*/  SMBFLG2_KNOWS_LONG_NAMES ; 
 int /*<<< orphan*/  SMBFLG2_SECURITY_SIGNATURE ; 
 int /*<<< orphan*/  SMBFLG2_UNICODE ; 
 int SMBFLG_CASELESS ; 
 int SMB_SHARE_IS_IN_DFS ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_next_mid (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
header_assemble(struct smb_hdr *buffer, char smb_command /* command */ ,
		const struct cifs_tcon *treeCon, int word_count
		/* length of fixed section (word count) in two byte units  */)
{
	char *temp = (char *) buffer;

	memset(temp, 0, 256); /* bigger than MAX_CIFS_HDR_SIZE */

	buffer->smb_buf_length = cpu_to_be32(
	    (2 * word_count) + sizeof(struct smb_hdr) -
	    4 /*  RFC 1001 length field does not count */  +
	    2 /* for bcc field itself */) ;

	buffer->Protocol[0] = 0xFF;
	buffer->Protocol[1] = 'S';
	buffer->Protocol[2] = 'M';
	buffer->Protocol[3] = 'B';
	buffer->Command = smb_command;
	buffer->Flags = 0x00;	/* case sensitive */
	buffer->Flags2 = SMBFLG2_KNOWS_LONG_NAMES;
	buffer->Pid = cpu_to_le16((__u16)current->tgid);
	buffer->PidHigh = cpu_to_le16((__u16)(current->tgid >> 16));
	if (treeCon) {
		buffer->Tid = treeCon->tid;
		if (treeCon->ses) {
			if (treeCon->ses->capabilities & CAP_UNICODE)
				buffer->Flags2 |= SMBFLG2_UNICODE;
			if (treeCon->ses->capabilities & CAP_STATUS32)
				buffer->Flags2 |= SMBFLG2_ERR_STATUS;

			/* Uid is not converted */
			buffer->Uid = treeCon->ses->Suid;
			buffer->Mid = get_next_mid(treeCon->ses->server);
		}
		if (treeCon->Flags & SMB_SHARE_IS_IN_DFS)
			buffer->Flags2 |= SMBFLG2_DFS;
		if (treeCon->nocase)
			buffer->Flags  |= SMBFLG_CASELESS;
		if ((treeCon->ses) && (treeCon->ses->server))
			if (treeCon->ses->server->sign)
				buffer->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;
	}

/*  endian conversion of flags is now done just before sending */
	buffer->WordCount = (char) word_count;
	return;
}