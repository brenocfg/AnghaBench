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
struct smb2_preauth_neg_context {int dummy; } ;
struct smb2_posix_neg_context {int dummy; } ;
struct smb2_negotiate_req {int /*<<< orphan*/  NegotiateContextCount; int /*<<< orphan*/  NegotiateContextOffset; } ;
struct smb2_encryption_neg_context {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int OFFSET_OF_NEG_CONTEXT ; 
 int /*<<< orphan*/  build_encrypt_ctxt (struct smb2_encryption_neg_context*) ; 
 int /*<<< orphan*/  build_posix_ctxt (struct smb2_posix_neg_context*) ; 
 int /*<<< orphan*/  build_preauth_ctxt (struct smb2_preauth_neg_context*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void
assemble_neg_contexts(struct smb2_negotiate_req *req,
		      unsigned int *total_len)
{
	char *pneg_ctxt = (char *)req + OFFSET_OF_NEG_CONTEXT;
	unsigned int ctxt_len;

	*total_len += 2; /* Add 2 due to round to 8 byte boundary for 1st ctxt */
	build_preauth_ctxt((struct smb2_preauth_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(sizeof(struct smb2_preauth_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_encrypt_ctxt((struct smb2_encryption_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(sizeof(struct smb2_encryption_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_posix_ctxt((struct smb2_posix_neg_context *)pneg_ctxt);
	*total_len += sizeof(struct smb2_posix_neg_context);

	req->NegotiateContextOffset = cpu_to_le32(OFFSET_OF_NEG_CONTEXT);
	req->NegotiateContextCount = cpu_to_le16(3);
}