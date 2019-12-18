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
struct smb2_preauth_neg_context {int /*<<< orphan*/  HashAlgorithms; int /*<<< orphan*/  Salt; void* SaltLength; void* HashAlgorithmCount; void* DataLength; int /*<<< orphan*/  ContextType; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_PREAUTH_INTEGRITY_CAPABILITIES ; 
 int /*<<< orphan*/  SMB2_PREAUTH_INTEGRITY_SHA512 ; 
 int SMB311_SALT_SIZE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
build_preauth_ctxt(struct smb2_preauth_neg_context *pneg_ctxt)
{
	pneg_ctxt->ContextType = SMB2_PREAUTH_INTEGRITY_CAPABILITIES;
	pneg_ctxt->DataLength = cpu_to_le16(38);
	pneg_ctxt->HashAlgorithmCount = cpu_to_le16(1);
	pneg_ctxt->SaltLength = cpu_to_le16(SMB311_SALT_SIZE);
	get_random_bytes(pneg_ctxt->Salt, SMB311_SALT_SIZE);
	pneg_ctxt->HashAlgorithms = SMB2_PREAUTH_INTEGRITY_SHA512;
}