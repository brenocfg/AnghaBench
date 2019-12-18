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
struct TYPE_2__ {scalar_t__ CifsError; } ;
struct smb_hdr {scalar_t__ WordCount; TYPE_1__ Status; int /*<<< orphan*/  smb_buf_length; } ;
struct TCP_Server_Info {int dummy; } ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  VFS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ check_smb_hdr (struct smb_hdr*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int get_mid (struct smb_hdr*) ; 
 int smbCalcSize (struct smb_hdr*,struct TCP_Server_Info*) ; 

int
checkSMB(char *buf, unsigned int total_read, struct TCP_Server_Info *server)
{
	struct smb_hdr *smb = (struct smb_hdr *)buf;
	__u32 rfclen = be32_to_cpu(smb->smb_buf_length);
	__u32 clc_len;  /* calculated length */
	cifs_dbg(FYI, "checkSMB Length: 0x%x, smb_buf_length: 0x%x\n",
		 total_read, rfclen);

	/* is this frame too small to even get to a BCC? */
	if (total_read < 2 + sizeof(struct smb_hdr)) {
		if ((total_read >= sizeof(struct smb_hdr) - 1)
			    && (smb->Status.CifsError != 0)) {
			/* it's an error return */
			smb->WordCount = 0;
			/* some error cases do not return wct and bcc */
			return 0;
		} else if ((total_read == sizeof(struct smb_hdr) + 1) &&
				(smb->WordCount == 0)) {
			char *tmp = (char *)smb;
			/* Need to work around a bug in two servers here */
			/* First, check if the part of bcc they sent was zero */
			if (tmp[sizeof(struct smb_hdr)] == 0) {
				/* some servers return only half of bcc
				 * on simple responses (wct, bcc both zero)
				 * in particular have seen this on
				 * ulogoffX and FindClose. This leaves
				 * one byte of bcc potentially unitialized
				 */
				/* zero rest of bcc */
				tmp[sizeof(struct smb_hdr)+1] = 0;
				return 0;
			}
			cifs_dbg(VFS, "rcvd invalid byte count (bcc)\n");
		} else {
			cifs_dbg(VFS, "Length less than smb header size\n");
		}
		return -EIO;
	}

	/* otherwise, there is enough to get to the BCC */
	if (check_smb_hdr(smb))
		return -EIO;
	clc_len = smbCalcSize(smb, server);

	if (4 + rfclen != total_read) {
		cifs_dbg(VFS, "Length read does not match RFC1001 length %d\n",
			 rfclen);
		return -EIO;
	}

	if (4 + rfclen != clc_len) {
		__u16 mid = get_mid(smb);
		/* check if bcc wrapped around for large read responses */
		if ((rfclen > 64 * 1024) && (rfclen > clc_len)) {
			/* check if lengths match mod 64K */
			if (((4 + rfclen) & 0xFFFF) == (clc_len & 0xFFFF))
				return 0; /* bcc wrapped */
		}
		cifs_dbg(FYI, "Calculated size %u vs length %u mismatch for mid=%u\n",
			 clc_len, 4 + rfclen, mid);

		if (4 + rfclen < clc_len) {
			cifs_dbg(VFS, "RFC1001 size %u smaller than SMB for mid=%u\n",
				 rfclen, mid);
			return -EIO;
		} else if (rfclen > clc_len + 512) {
			/*
			 * Some servers (Windows XP in particular) send more
			 * data than the lengths in the SMB packet would
			 * indicate on certain calls (byte range locks and
			 * trans2 find first calls in particular). While the
			 * client can handle such a frame by ignoring the
			 * trailing data, we choose limit the amount of extra
			 * data to 512 bytes.
			 */
			cifs_dbg(VFS, "RFC1001 size %u more than 512 bytes larger than SMB for mid=%u\n",
				 rfclen, mid);
			return -EIO;
		}
	}
	return 0;
}