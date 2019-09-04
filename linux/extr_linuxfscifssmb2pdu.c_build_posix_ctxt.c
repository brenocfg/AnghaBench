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
struct smb2_posix_neg_context {int /*<<< orphan*/  DataLength; int /*<<< orphan*/  ContextType; } ;

/* Variables and functions */
 int /*<<< orphan*/  POSIX_CTXT_DATA_LEN ; 
 int /*<<< orphan*/  SMB2_POSIX_EXTENSIONS_AVAILABLE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_posix_ctxt(struct smb2_posix_neg_context *pneg_ctxt)
{
	pneg_ctxt->ContextType = SMB2_POSIX_EXTENSIONS_AVAILABLE;
	pneg_ctxt->DataLength = cpu_to_le16(POSIX_CTXT_DATA_LEN);
}