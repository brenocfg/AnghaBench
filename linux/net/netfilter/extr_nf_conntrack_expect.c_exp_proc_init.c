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
struct proc_dir_entry {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  proc_net; } ;
struct ct_expect_iter_state {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  exp_seq_ops ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* proc_create_net (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_set_user (struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exp_proc_init(struct net *net)
{
#ifdef CONFIG_NF_CONNTRACK_PROCFS
	struct proc_dir_entry *proc;
	kuid_t root_uid;
	kgid_t root_gid;

	proc = proc_create_net("nf_conntrack_expect", 0440, net->proc_net,
			&exp_seq_ops, sizeof(struct ct_expect_iter_state));
	if (!proc)
		return -ENOMEM;

	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);
	if (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);
#endif /* CONFIG_NF_CONNTRACK_PROCFS */
	return 0;
}