#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct nf_conn_help {int /*<<< orphan*/  data; TYPE_1__* helper; } ;
struct nf_conn {int dummy; } ;
struct TYPE_2__ {scalar_t__ data_len; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfnl_cthelper_from_nlattr(struct nlattr *attr, struct nf_conn *ct)
{
	struct nf_conn_help *help = nfct_help(ct);

	if (attr == NULL)
		return -EINVAL;

	if (help->helper->data_len == 0)
		return -EINVAL;

	nla_memcpy(help->data, nla_data(attr), sizeof(help->data));
	return 0;
}