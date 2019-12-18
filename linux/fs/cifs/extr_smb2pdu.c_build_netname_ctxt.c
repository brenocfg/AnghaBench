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
struct smb2_netname_neg_context {int /*<<< orphan*/  DataLength; int /*<<< orphan*/  NetName; int /*<<< orphan*/  ContextType; } ;
struct smb2_neg_context {int dummy; } ;
struct nls_table {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int /*<<< orphan*/  SMB2_NETNAME_NEGOTIATE_CONTEXT_ID ; 
 int cifs_strtoUTF16 (int /*<<< orphan*/ ,char*,int,struct nls_table*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct nls_table* load_nls_default () ; 

__attribute__((used)) static unsigned int
build_netname_ctxt(struct smb2_netname_neg_context *pneg_ctxt, char *hostname)
{
	struct nls_table *cp = load_nls_default();

	pneg_ctxt->ContextType = SMB2_NETNAME_NEGOTIATE_CONTEXT_ID;

	/* copy up to max of first 100 bytes of server name to NetName field */
	pneg_ctxt->DataLength = cpu_to_le16(2 * cifs_strtoUTF16(pneg_ctxt->NetName, hostname, 100, cp));
	/* context size is DataLength + minimal smb2_neg_context */
	return DIV_ROUND_UP(le16_to_cpu(pneg_ctxt->DataLength) +
			sizeof(struct smb2_neg_context), 8) * 8;
}