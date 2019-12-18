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
union bpf_attr {int prog_btf_fd; int log_level; unsigned int line_info_rec_size; unsigned int line_info_cnt; void* line_info; int /*<<< orphan*/  log_size; void* log_buf; void* func_info; int /*<<< orphan*/  func_info_cnt; int /*<<< orphan*/  func_info_rec_size; void* license; int /*<<< orphan*/  insn_cnt; void* insns; int /*<<< orphan*/  prog_type; } ;
struct prog_info_raw_test {char* descr; char const* str_sec; void* insns; void* func_info; unsigned int line_info_rec_size; int expected_prog_load_failure; scalar_t__ dead_code_cnt; int /*<<< orphan*/  err_str; int /*<<< orphan*/  func_info_cnt; int /*<<< orphan*/  func_info_rec_size; int /*<<< orphan*/  prog_type; int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  line_info; int /*<<< orphan*/  raw_types; } ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_2__ {scalar_t__ always_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_LOAD ; 
 int /*<<< orphan*/  BTF_LOG_BUF_SIZE ; 
 scalar_t__ CHECK (int,char*,int,...) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  __NR_bpf ; 
 TYPE_1__ args ; 
 int bpf_load_btf (void*,unsigned int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* btf_log_buf ; 
 void* btf_raw_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,unsigned int*,char const**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hdr_tmpl ; 
 struct prog_info_raw_test* info_raw_tests ; 
 void* patch_name_tbd (int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  probe_prog_length (void*) ; 
 void* ptr_to_u64 (void*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strstr (char*,int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union bpf_attr*,int) ; 
 int test_get_finfo (struct prog_info_raw_test const*,int) ; 
 int test_get_linfo (struct prog_info_raw_test const*,void*,scalar_t__,int) ; 

__attribute__((used)) static int do_test_info_raw(unsigned int test_num)
{
	const struct prog_info_raw_test *test = &info_raw_tests[test_num - 1];
	unsigned int raw_btf_size, linfo_str_off, linfo_size;
	int btf_fd = -1, prog_fd = -1, err = 0;
	void *raw_btf, *patched_linfo = NULL;
	const char *ret_next_str;
	union bpf_attr attr = {};

	fprintf(stderr, "BTF prog info raw test[%u] (%s): ", test_num, test->descr);
	raw_btf = btf_raw_create(&hdr_tmpl, test->raw_types,
				 test->str_sec, test->str_sec_size,
				 &raw_btf_size, &ret_next_str);

	if (!raw_btf)
		return -1;

	*btf_log_buf = '\0';
	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      args.always_log);
	free(raw_btf);

	if (CHECK(btf_fd == -1, "invalid btf_fd errno:%d", errno)) {
		err = -1;
		goto done;
	}

	if (*btf_log_buf && args.always_log)
		fprintf(stderr, "\n%s", btf_log_buf);
	*btf_log_buf = '\0';

	linfo_str_off = ret_next_str - test->str_sec;
	patched_linfo = patch_name_tbd(test->line_info,
				       test->str_sec, linfo_str_off,
				       test->str_sec_size, &linfo_size);
	if (IS_ERR(patched_linfo)) {
		fprintf(stderr, "error in creating raw bpf_line_info");
		err = -1;
		goto done;
	}

	attr.prog_type = test->prog_type;
	attr.insns = ptr_to_u64(test->insns);
	attr.insn_cnt = probe_prog_length(test->insns);
	attr.license = ptr_to_u64("GPL");
	attr.prog_btf_fd = btf_fd;
	attr.func_info_rec_size = test->func_info_rec_size;
	attr.func_info_cnt = test->func_info_cnt;
	attr.func_info = ptr_to_u64(test->func_info);
	attr.log_buf = ptr_to_u64(btf_log_buf);
	attr.log_size = BTF_LOG_BUF_SIZE;
	attr.log_level = 1;
	if (linfo_size) {
		attr.line_info_rec_size = test->line_info_rec_size;
		attr.line_info = ptr_to_u64(patched_linfo);
		attr.line_info_cnt = linfo_size / attr.line_info_rec_size;
	}

	prog_fd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, sizeof(attr));
	err = ((prog_fd == -1) != test->expected_prog_load_failure);
	if (CHECK(err, "prog_fd:%d expected_prog_load_failure:%u errno:%d",
		  prog_fd, test->expected_prog_load_failure, errno) ||
	    CHECK(test->err_str && !strstr(btf_log_buf, test->err_str),
		  "expected err_str:%s", test->err_str)) {
		err = -1;
		goto done;
	}

	if (prog_fd == -1)
		goto done;

	err = test_get_finfo(test, prog_fd);
	if (err)
		goto done;

	err = test_get_linfo(test, patched_linfo,
			     attr.line_info_cnt - test->dead_code_cnt,
			     prog_fd);
	if (err)
		goto done;

done:
	if (!err)
		fprintf(stderr, "OK");

	if (*btf_log_buf && (err || args.always_log))
		fprintf(stderr, "\n%s", btf_log_buf);

	if (btf_fd != -1)
		close(btf_fd);
	if (prog_fd != -1)
		close(prog_fd);

	if (!IS_ERR(patched_linfo))
		free(patched_linfo);

	return err;
}