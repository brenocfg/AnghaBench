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
struct nf_conntrack_expect {int /*<<< orphan*/  master; } ;
struct nf_conn_help {TYPE_1__* helper; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool expect_iter_name(struct nf_conntrack_expect *exp, void *data)
{
	const struct nf_conn_help *m_help;
	const char *name = data;

	m_help = nfct_help(exp->master);

	return strcmp(m_help->helper->name, name) == 0;
}