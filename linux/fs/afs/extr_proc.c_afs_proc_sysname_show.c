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
struct seq_file {int dummy; } ;
struct afs_sysnames {unsigned int nr; int /*<<< orphan*/ * subs; } ;
struct afs_net {struct afs_sysnames* sysnames; } ;

/* Variables and functions */
 struct afs_net* afs_seq2net (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_proc_sysname_show(struct seq_file *m, void *v)
{
	struct afs_net *net = afs_seq2net(m);
	struct afs_sysnames *sysnames = net->sysnames;
	unsigned int i = (unsigned long)v - 1;

	if (i < sysnames->nr)
		seq_printf(m, "%s\n", sysnames->subs[i]);
	return 0;
}