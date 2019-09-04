#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union bpf_attr {int prog_type; int prog_flags; scalar_t__ insn_cnt; scalar_t__ kern_version; int /*<<< orphan*/  prog_name; int /*<<< orphan*/  insns; int /*<<< orphan*/  prog_ifindex; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  license; } ;
struct bpf_prog {scalar_t__ len; int gpl_compatible; TYPE_1__* aux; scalar_t__ jited; int /*<<< orphan*/ * orig_prog; int /*<<< orphan*/  insns; int /*<<< orphan*/  expected_attach_type; } ;
typedef  int /*<<< orphan*/  license ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
struct TYPE_5__ {int offload_requested; int /*<<< orphan*/  name; int /*<<< orphan*/  load_time; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int BPF_F_STRICT_ALIGNMENT ; 
 scalar_t__ BPF_MAXINSNS ; 
 int /*<<< orphan*/  BPF_PROG_LOAD ; 
 int BPF_PROG_TYPE_CGROUP_SKB ; 
 int BPF_PROG_TYPE_KPROBE ; 
 int BPF_PROG_TYPE_SOCKET_FILTER ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int E2BIG ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_USER ; 
 scalar_t__ LINUX_VERSION_CODE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int bpf_check (struct bpf_prog**,union bpf_attr*) ; 
 int bpf_obj_name_cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bpf_prog* bpf_prog_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_alloc_id (struct bpf_prog*) ; 
 int bpf_prog_charge_memlock (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_free (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_insn_size (struct bpf_prog*) ; 
 scalar_t__ bpf_prog_is_dev_bound (TYPE_1__*) ; 
 int /*<<< orphan*/  bpf_prog_kallsyms_add (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_kallsyms_del_subprogs (struct bpf_prog*) ; 
 scalar_t__ bpf_prog_load_check_attach_type (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_load_fixup_attach_type (union bpf_attr*) ; 
 int bpf_prog_new_fd (struct bpf_prog*) ; 
 int bpf_prog_offload_init (struct bpf_prog*,union bpf_attr*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct bpf_prog* bpf_prog_select_runtime (struct bpf_prog*,int*) ; 
 int /*<<< orphan*/  bpf_prog_size (scalar_t__) ; 
 int /*<<< orphan*/  bpf_prog_uncharge_memlock (struct bpf_prog*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_prog_type (int,struct bpf_prog*) ; 
 int /*<<< orphan*/  free_used_maps (TYPE_1__*) ; 
 int /*<<< orphan*/  ktime_get_boot_ns () ; 
 int license_is_gpl_compatible (char*) ; 
 int security_bpf_prog_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  security_bpf_prog_free (TYPE_1__*) ; 
 scalar_t__ strncpy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_prog_load(union bpf_attr *attr)
{
	enum bpf_prog_type type = attr->prog_type;
	struct bpf_prog *prog;
	int err;
	char license[128];
	bool is_gpl;

	if (CHECK_ATTR(BPF_PROG_LOAD))
		return -EINVAL;

	if (attr->prog_flags & ~BPF_F_STRICT_ALIGNMENT)
		return -EINVAL;

	/* copy eBPF program license from user space */
	if (strncpy_from_user(license, u64_to_user_ptr(attr->license),
			      sizeof(license) - 1) < 0)
		return -EFAULT;
	license[sizeof(license) - 1] = 0;

	/* eBPF programs must be GPL compatible to use GPL-ed functions */
	is_gpl = license_is_gpl_compatible(license);

	if (attr->insn_cnt == 0 || attr->insn_cnt > BPF_MAXINSNS)
		return -E2BIG;

	if (type == BPF_PROG_TYPE_KPROBE &&
	    attr->kern_version != LINUX_VERSION_CODE)
		return -EINVAL;

	if (type != BPF_PROG_TYPE_SOCKET_FILTER &&
	    type != BPF_PROG_TYPE_CGROUP_SKB &&
	    !capable(CAP_SYS_ADMIN))
		return -EPERM;

	bpf_prog_load_fixup_attach_type(attr);
	if (bpf_prog_load_check_attach_type(type, attr->expected_attach_type))
		return -EINVAL;

	/* plain bpf_prog allocation */
	prog = bpf_prog_alloc(bpf_prog_size(attr->insn_cnt), GFP_USER);
	if (!prog)
		return -ENOMEM;

	prog->expected_attach_type = attr->expected_attach_type;

	prog->aux->offload_requested = !!attr->prog_ifindex;

	err = security_bpf_prog_alloc(prog->aux);
	if (err)
		goto free_prog_nouncharge;

	err = bpf_prog_charge_memlock(prog);
	if (err)
		goto free_prog_sec;

	prog->len = attr->insn_cnt;

	err = -EFAULT;
	if (copy_from_user(prog->insns, u64_to_user_ptr(attr->insns),
			   bpf_prog_insn_size(prog)) != 0)
		goto free_prog;

	prog->orig_prog = NULL;
	prog->jited = 0;

	atomic_set(&prog->aux->refcnt, 1);
	prog->gpl_compatible = is_gpl ? 1 : 0;

	if (bpf_prog_is_dev_bound(prog->aux)) {
		err = bpf_prog_offload_init(prog, attr);
		if (err)
			goto free_prog;
	}

	/* find program type: socket_filter vs tracing_filter */
	err = find_prog_type(type, prog);
	if (err < 0)
		goto free_prog;

	prog->aux->load_time = ktime_get_boot_ns();
	err = bpf_obj_name_cpy(prog->aux->name, attr->prog_name);
	if (err)
		goto free_prog;

	/* run eBPF verifier */
	err = bpf_check(&prog, attr);
	if (err < 0)
		goto free_used_maps;

	prog = bpf_prog_select_runtime(prog, &err);
	if (err < 0)
		goto free_used_maps;

	err = bpf_prog_alloc_id(prog);
	if (err)
		goto free_used_maps;

	err = bpf_prog_new_fd(prog);
	if (err < 0) {
		/* failed to allocate fd.
		 * bpf_prog_put() is needed because the above
		 * bpf_prog_alloc_id() has published the prog
		 * to the userspace and the userspace may
		 * have refcnt-ed it through BPF_PROG_GET_FD_BY_ID.
		 */
		bpf_prog_put(prog);
		return err;
	}

	bpf_prog_kallsyms_add(prog);
	return err;

free_used_maps:
	bpf_prog_kallsyms_del_subprogs(prog);
	free_used_maps(prog->aux);
free_prog:
	bpf_prog_uncharge_memlock(prog);
free_prog_sec:
	security_bpf_prog_free(prog->aux);
free_prog_nouncharge:
	bpf_prog_free(prog);
	return err;
}