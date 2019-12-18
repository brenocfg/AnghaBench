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
struct smb2_neg_context {int dummy; } ;
struct smb2_compression_capabilities_context {int /*<<< orphan*/ * CompressionAlgorithms; void* CompressionAlgorithmCount; void* DataLength; int /*<<< orphan*/  ContextType; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_COMPRESSION_CAPABILITIES ; 
 int /*<<< orphan*/  SMB3_COMPRESS_LZ77 ; 
 int /*<<< orphan*/  SMB3_COMPRESS_LZ77_HUFF ; 
 int /*<<< orphan*/  SMB3_COMPRESS_LZNT1 ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
build_compression_ctxt(struct smb2_compression_capabilities_context *pneg_ctxt)
{
	pneg_ctxt->ContextType = SMB2_COMPRESSION_CAPABILITIES;
	pneg_ctxt->DataLength =
		cpu_to_le16(sizeof(struct smb2_compression_capabilities_context)
			  - sizeof(struct smb2_neg_context));
	pneg_ctxt->CompressionAlgorithmCount = cpu_to_le16(3);
	pneg_ctxt->CompressionAlgorithms[0] = SMB3_COMPRESS_LZ77;
	pneg_ctxt->CompressionAlgorithms[1] = SMB3_COMPRESS_LZ77_HUFF;
	pneg_ctxt->CompressionAlgorithms[2] = SMB3_COMPRESS_LZNT1;
}