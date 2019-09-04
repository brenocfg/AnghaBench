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
struct nlattr {int dummy; } ;
struct nf_ct_ftp_master {int /*<<< orphan*/ * flags; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  NF_CT_FTP_SEQ_PICKUP ; 
 struct nf_ct_ftp_master* nfct_help_data (struct nf_conn*) ; 

__attribute__((used)) static int nf_ct_ftp_from_nlattr(struct nlattr *attr, struct nf_conn *ct)
{
	struct nf_ct_ftp_master *ftp = nfct_help_data(ct);

	/* This conntrack has been injected from user-space, always pick up
	 * sequence tracking. Otherwise, the first FTP command after the
	 * failover breaks.
	 */
	ftp->flags[IP_CT_DIR_ORIGINAL] |= NF_CT_FTP_SEQ_PICKUP;
	ftp->flags[IP_CT_DIR_REPLY] |= NF_CT_FTP_SEQ_PICKUP;
	return 0;
}