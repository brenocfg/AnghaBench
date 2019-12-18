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
typedef  size_t u_int8_t ;
struct seq_net_private {int dummy; } ;
struct proc_dir_entry {int dummy; } ;
struct nf_mttg_trav {int dummy; } ;
struct net {int /*<<< orphan*/  proc_net; int /*<<< orphan*/  user_ns; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FORMAT_MATCHES ; 
 int /*<<< orphan*/  FORMAT_TABLES ; 
 int /*<<< orphan*/  FORMAT_TARGETS ; 
 int XT_FUNCTION_MAXNAMELEN ; 
 scalar_t__ gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* proc_create_net_data (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 
 struct proc_dir_entry* proc_create_seq_private (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  proc_set_user (struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_match_seq_ops ; 
 int /*<<< orphan*/ * xt_prefix ; 
 int /*<<< orphan*/  xt_table_seq_ops ; 
 int /*<<< orphan*/  xt_target_seq_ops ; 

int xt_proto_init(struct net *net, u_int8_t af)
{
#ifdef CONFIG_PROC_FS
	char buf[XT_FUNCTION_MAXNAMELEN];
	struct proc_dir_entry *proc;
	kuid_t root_uid;
	kgid_t root_gid;
#endif

	if (af >= ARRAY_SIZE(xt_prefix))
		return -EINVAL;


#ifdef CONFIG_PROC_FS
	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	proc = proc_create_net_data(buf, 0440, net->proc_net, &xt_table_seq_ops,
			sizeof(struct seq_net_private),
			(void *)(unsigned long)af);
	if (!proc)
		goto out;
	if (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	proc = proc_create_seq_private(buf, 0440, net->proc_net,
			&xt_match_seq_ops, sizeof(struct nf_mttg_trav),
			(void *)(unsigned long)af);
	if (!proc)
		goto out_remove_tables;
	if (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TARGETS, sizeof(buf));
	proc = proc_create_seq_private(buf, 0440, net->proc_net,
			 &xt_target_seq_ops, sizeof(struct nf_mttg_trav),
			 (void *)(unsigned long)af);
	if (!proc)
		goto out_remove_matches;
	if (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);
#endif

	return 0;

#ifdef CONFIG_PROC_FS
out_remove_matches:
	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);

out_remove_tables:
	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);
out:
	return -1;
#endif
}