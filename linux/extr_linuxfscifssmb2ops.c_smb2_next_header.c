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
struct smb2_transform_hdr {int /*<<< orphan*/  OriginalMessageSize; } ;
struct smb2_sync_hdr {scalar_t__ ProtocolId; int /*<<< orphan*/  NextCommand; } ;

/* Variables and functions */
 scalar_t__ SMB2_TRANSFORM_PROTO_NUM ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb2_next_header(char *buf)
{
	struct smb2_sync_hdr *hdr = (struct smb2_sync_hdr *)buf;
	struct smb2_transform_hdr *t_hdr = (struct smb2_transform_hdr *)buf;

	if (hdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM)
		return sizeof(struct smb2_transform_hdr) +
		  le32_to_cpu(t_hdr->OriginalMessageSize);

	return le32_to_cpu(hdr->NextCommand);
}