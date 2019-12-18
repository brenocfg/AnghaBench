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
struct smb2_encryption_neg_context {int /*<<< orphan*/ * Ciphers; void* CipherCount; void* DataLength; int /*<<< orphan*/  ContextType; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_ENCRYPTION_AES128_CCM ; 
 int /*<<< orphan*/  SMB2_ENCRYPTION_AES128_GCM ; 
 int /*<<< orphan*/  SMB2_ENCRYPTION_CAPABILITIES ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
build_encrypt_ctxt(struct smb2_encryption_neg_context *pneg_ctxt)
{
	pneg_ctxt->ContextType = SMB2_ENCRYPTION_CAPABILITIES;
	pneg_ctxt->DataLength = cpu_to_le16(6); /* Cipher Count + two ciphers */
	pneg_ctxt->CipherCount = cpu_to_le16(2);
	pneg_ctxt->Ciphers[0] = SMB2_ENCRYPTION_AES128_GCM;
	pneg_ctxt->Ciphers[1] = SMB2_ENCRYPTION_AES128_CCM;
}