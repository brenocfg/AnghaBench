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
typedef  scalar_t__ u_int8_t ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  xt_prefix ; 

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