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
struct xt_tgdtor_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct xt_ct_target_info_v1 {struct nf_conn* ct; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_helper_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_destroy_timeout (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 

__attribute__((used)) static void xt_ct_tg_destroy(const struct xt_tgdtor_param *par,
			     struct xt_ct_target_info_v1 *info)
{
	struct nf_conn *ct = info->ct;
	struct nf_conn_help *help;

	if (ct) {
		help = nfct_help(ct);
		if (help)
			nf_conntrack_helper_put(help->helper);

		nf_ct_netns_put(par->net, par->family);

		nf_ct_destroy_timeout(ct);
		nf_ct_put(info->ct);
	}
}