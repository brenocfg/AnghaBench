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
struct proc_dir_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_net_sctp; } ;
struct net {TYPE_1__ sctp; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct proc_dir_entry* proc_create_seq (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_objcnt_seq_ops ; 

void sctp_dbg_objcnt_init(struct net *net)
{
	struct proc_dir_entry *ent;

	ent = proc_create_seq("sctp_dbg_objcnt", 0,
			  net->sctp.proc_net_sctp, &sctp_objcnt_seq_ops);
	if (!ent)
		pr_warn("sctp_dbg_objcnt: Unable to create /proc entry.\n");
}