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
struct smb2_netname_neg_context {int dummy; } ;
struct smb2_negotiate_req {void* NegotiateContextCount; int /*<<< orphan*/  NegotiateContextOffset; } ;
struct smb2_encryption_neg_context {int dummy; } ;
struct smb2_compression_capabilities_context {int dummy; } ;
struct TCP_Server_Info {int /*<<< orphan*/  hostname; scalar_t__ compress_algorithm; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  build_compression_ctxt (struct smb2_compression_capabilities_context*) ; 
 int /*<<< orphan*/  build_encrypt_ctxt (struct smb2_encryption_neg_context*) ; 
 unsigned int build_netname_ctxt (struct smb2_netname_neg_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_posix_ctxt (struct smb2_posix_neg_context*) ; 
 int /*<<< orphan*/  build_preauth_ctxt (struct smb2_preauth_neg_context*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int roundup (unsigned int,int) ; 

__attribute__((used)) static void
assemble_neg_contexts(struct smb2_negotiate_req *req,
		      struct TCP_Server_Info *server, unsigned int *total_len)
{
	char *pneg_ctxt = (char *)req;
	unsigned int ctxt_len;

	if (*total_len > 200) {
		/* In case length corrupted don't want to overrun smb buffer */
		cifs_server_dbg(VFS, "Bad frame length assembling neg contexts\n");
		return;
	}

	/*
	 * round up total_len of fixed part of SMB3 negotiate request to 8
	 * byte boundary before adding negotiate contexts
	 */
	*total_len = roundup(*total_len, 8);

	pneg_ctxt = (*total_len) + (char *)req;
	req->NegotiateContextOffset = cpu_to_le32(*total_len);

	build_preauth_ctxt((struct smb2_preauth_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(sizeof(struct smb2_preauth_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_encrypt_ctxt((struct smb2_encryption_neg_context *)pneg_ctxt);
	ctxt_len = DIV_ROUND_UP(sizeof(struct smb2_encryption_neg_context), 8) * 8;
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	if (server->compress_algorithm) {
		build_compression_ctxt((struct smb2_compression_capabilities_context *)
				pneg_ctxt);
		ctxt_len = DIV_ROUND_UP(
			sizeof(struct smb2_compression_capabilities_context),
				8) * 8;
		*total_len += ctxt_len;
		pneg_ctxt += ctxt_len;
		req->NegotiateContextCount = cpu_to_le16(5);
	} else
		req->NegotiateContextCount = cpu_to_le16(4);

	ctxt_len = build_netname_ctxt((struct smb2_netname_neg_context *)pneg_ctxt,
					server->hostname);
	*total_len += ctxt_len;
	pneg_ctxt += ctxt_len;

	build_posix_ctxt((struct smb2_posix_neg_context *)pneg_ctxt);
	*total_len += sizeof(struct smb2_posix_neg_context);
}