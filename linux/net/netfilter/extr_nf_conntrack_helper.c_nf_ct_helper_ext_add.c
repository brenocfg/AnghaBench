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
struct nf_conn_help {int /*<<< orphan*/  expectations; } ;
struct nf_conn {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NF_CT_EXT_HELPER ; 
 struct nf_conn_help* nf_ct_ext_add (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct nf_conn_help *
nf_ct_helper_ext_add(struct nf_conn *ct, gfp_t gfp)
{
	struct nf_conn_help *help;

	help = nf_ct_ext_add(ct, NF_CT_EXT_HELPER, gfp);
	if (help)
		INIT_HLIST_HEAD(&help->expectations);
	else
		pr_debug("failed to add helper extension area");
	return help;
}