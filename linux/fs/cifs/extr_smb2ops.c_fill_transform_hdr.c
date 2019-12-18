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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct smb2_transform_hdr {int /*<<< orphan*/  SessionId; int /*<<< orphan*/  Nonce; int /*<<< orphan*/  Flags; int /*<<< orphan*/  OriginalMessageSize; int /*<<< orphan*/  ProtocolId; } ;
struct smb2_sync_hdr {int /*<<< orphan*/  SessionId; } ;
typedef  scalar_t__ __le16 ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 scalar_t__ SMB2_ENCRYPTION_AES128_GCM ; 
 int /*<<< orphan*/  SMB2_TRANSFORM_PROTO_NUM ; 
 int /*<<< orphan*/  SMB3_AES128CCM_NONCE ; 
 int /*<<< orphan*/  SMB3_AES128GCM_NONCE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct smb2_transform_hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fill_transform_hdr(struct smb2_transform_hdr *tr_hdr, unsigned int orig_len,
		   struct smb_rqst *old_rq, __le16 cipher_type)
{
	struct smb2_sync_hdr *shdr =
			(struct smb2_sync_hdr *)old_rq->rq_iov[0].iov_base;

	memset(tr_hdr, 0, sizeof(struct smb2_transform_hdr));
	tr_hdr->ProtocolId = SMB2_TRANSFORM_PROTO_NUM;
	tr_hdr->OriginalMessageSize = cpu_to_le32(orig_len);
	tr_hdr->Flags = cpu_to_le16(0x01);
	if (cipher_type == SMB2_ENCRYPTION_AES128_GCM)
		get_random_bytes(&tr_hdr->Nonce, SMB3_AES128GCM_NONCE);
	else
		get_random_bytes(&tr_hdr->Nonce, SMB3_AES128CCM_NONCE);
	memcpy(&tr_hdr->SessionId, &shdr->SessionId, 8);
}