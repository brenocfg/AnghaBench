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
struct TYPE_2__ {scalar_t__ data_size_out; int /*<<< orphan*/  duration; int /*<<< orphan*/  retval; int /*<<< orphan*/  ctx_size_out; int /*<<< orphan*/  repeat; int /*<<< orphan*/  ctx_size_in; void* ctx_out; void* ctx_in; int /*<<< orphan*/  data_size_in; void* data_out; void* data_in; int /*<<< orphan*/  prog_fd; } ;
union bpf_attr {TYPE_1__ test; } ;
struct bpf_prog_test_run_attr {scalar_t__ data_size_out; int /*<<< orphan*/  duration; int /*<<< orphan*/  retval; int /*<<< orphan*/  ctx_size_out; int /*<<< orphan*/  repeat; int /*<<< orphan*/  ctx_size_in; int /*<<< orphan*/  ctx_out; int /*<<< orphan*/  ctx_in; int /*<<< orphan*/  data_size_in; int /*<<< orphan*/  data_out; int /*<<< orphan*/  data_in; int /*<<< orphan*/  prog_fd; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TEST_RUN ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (union bpf_attr*,int /*<<< orphan*/ ,int) ; 
 void* ptr_to_u64 (int /*<<< orphan*/ ) ; 
 int sys_bpf (int /*<<< orphan*/ ,union bpf_attr*,int) ; 

int bpf_prog_test_run_xattr(struct bpf_prog_test_run_attr *test_attr)
{
	union bpf_attr attr;
	int ret;

	if (!test_attr->data_out && test_attr->data_size_out > 0)
		return -EINVAL;

	memset(&attr, 0, sizeof(attr));
	attr.test.prog_fd = test_attr->prog_fd;
	attr.test.data_in = ptr_to_u64(test_attr->data_in);
	attr.test.data_out = ptr_to_u64(test_attr->data_out);
	attr.test.data_size_in = test_attr->data_size_in;
	attr.test.data_size_out = test_attr->data_size_out;
	attr.test.ctx_in = ptr_to_u64(test_attr->ctx_in);
	attr.test.ctx_out = ptr_to_u64(test_attr->ctx_out);
	attr.test.ctx_size_in = test_attr->ctx_size_in;
	attr.test.ctx_size_out = test_attr->ctx_size_out;
	attr.test.repeat = test_attr->repeat;

	ret = sys_bpf(BPF_PROG_TEST_RUN, &attr, sizeof(attr));
	test_attr->data_size_out = attr.test.data_size_out;
	test_attr->ctx_size_out = attr.test.ctx_size_out;
	test_attr->retval = attr.test.retval;
	test_attr->duration = attr.test.duration;
	return ret;
}