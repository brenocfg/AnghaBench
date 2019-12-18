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
struct seq_file {int dummy; } ;
struct p9_client {int msize; int proto_version; TYPE_1__* trans_mod; } ;
struct TYPE_2__ {int name; int (* show_options ) (struct seq_file*,struct p9_client*) ;} ;

/* Variables and functions */
#define  p9_proto_2000L 130 
#define  p9_proto_2000u 129 
#define  p9_proto_legacy 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int stub1 (struct seq_file*,struct p9_client*) ; 

int p9_show_client_options(struct seq_file *m, struct p9_client *clnt)
{
	if (clnt->msize != 8192)
		seq_printf(m, ",msize=%u", clnt->msize);
	seq_printf(m, ",trans=%s", clnt->trans_mod->name);

	switch (clnt->proto_version) {
	case p9_proto_legacy:
		seq_puts(m, ",noextend");
		break;
	case p9_proto_2000u:
		seq_puts(m, ",version=9p2000.u");
		break;
	case p9_proto_2000L:
		/* Default */
		break;
	}

	if (clnt->trans_mod->show_options)
		return clnt->trans_mod->show_options(m, clnt);
	return 0;
}