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
struct TYPE_2__ {int /*<<< orphan*/  prog_fd; int /*<<< orphan*/  name; } ;
union bpf_attr {TYPE_1__ raw_tracepoint; } ;
typedef  int /*<<< orphan*/  tp_name ;
struct bpf_raw_tracepoint {struct bpf_raw_event_map* btp; struct bpf_prog* prog; } ;
struct bpf_raw_event_map {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_RAW_TRACEPOINT ; 
 int EFAULT ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PTR_ERR (struct bpf_prog*) ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct bpf_raw_tracepoint*,int /*<<< orphan*/ ) ; 
 struct bpf_raw_event_map* bpf_find_raw_tracepoint (char*) ; 
 int bpf_probe_register (struct bpf_raw_event_map*,struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_probe_unregister (struct bpf_raw_event_map*,struct bpf_prog*) ; 
 struct bpf_prog* bpf_prog_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_raw_tp_fops ; 
 int /*<<< orphan*/  kfree (struct bpf_raw_tracepoint*) ; 
 struct bpf_raw_tracepoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncpy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_raw_tracepoint_open(const union bpf_attr *attr)
{
	struct bpf_raw_tracepoint *raw_tp;
	struct bpf_raw_event_map *btp;
	struct bpf_prog *prog;
	char tp_name[128];
	int tp_fd, err;

	if (strncpy_from_user(tp_name, u64_to_user_ptr(attr->raw_tracepoint.name),
			      sizeof(tp_name) - 1) < 0)
		return -EFAULT;
	tp_name[sizeof(tp_name) - 1] = 0;

	btp = bpf_find_raw_tracepoint(tp_name);
	if (!btp)
		return -ENOENT;

	raw_tp = kzalloc(sizeof(*raw_tp), GFP_USER);
	if (!raw_tp)
		return -ENOMEM;
	raw_tp->btp = btp;

	prog = bpf_prog_get_type(attr->raw_tracepoint.prog_fd,
				 BPF_PROG_TYPE_RAW_TRACEPOINT);
	if (IS_ERR(prog)) {
		err = PTR_ERR(prog);
		goto out_free_tp;
	}

	err = bpf_probe_register(raw_tp->btp, prog);
	if (err)
		goto out_put_prog;

	raw_tp->prog = prog;
	tp_fd = anon_inode_getfd("bpf-raw-tracepoint", &bpf_raw_tp_fops, raw_tp,
				 O_CLOEXEC);
	if (tp_fd < 0) {
		bpf_probe_unregister(raw_tp->btp, prog);
		err = tp_fd;
		goto out_put_prog;
	}
	return tp_fd;

out_put_prog:
	bpf_prog_put(prog);
out_free_tp:
	kfree(raw_tp);
	return err;
}