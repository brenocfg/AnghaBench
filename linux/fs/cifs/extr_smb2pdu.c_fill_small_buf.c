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
struct smb2_sync_pdu {int /*<<< orphan*/  StructureSize2; int /*<<< orphan*/  sync_hdr; } ;
struct smb2_sync_hdr {int dummy; } ;
struct cifs_tcon {int dummy; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb2_hdr_assemble (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cifs_tcon*) ; 
 int* smb2_req_struct_sizes ; 

__attribute__((used)) static void
fill_small_buf(__le16 smb2_command, struct cifs_tcon *tcon, void *buf,
	       unsigned int *total_len)
{
	struct smb2_sync_pdu *spdu = (struct smb2_sync_pdu *)buf;
	/* lookup word count ie StructureSize from table */
	__u16 parmsize = smb2_req_struct_sizes[le16_to_cpu(smb2_command)];

	/*
	 * smaller than SMALL_BUFFER_SIZE but bigger than fixed area of
	 * largest operations (Create)
	 */
	memset(buf, 0, 256);

	smb2_hdr_assemble(&spdu->sync_hdr, smb2_command, tcon);
	spdu->StructureSize2 = cpu_to_le16(parmsize);

	*total_len = parmsize + sizeof(struct smb2_sync_hdr);
}