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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct btf_get_info_test {int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  str_sec; int /*<<< orphan*/  raw_types; } ;
struct bpf_btf_info {unsigned int btf_size; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  info_garbage ;
struct TYPE_2__ {scalar_t__ always_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_LOG_BUF_SIZE ; 
 scalar_t__ CHECK (int,char*,...) ; 
 TYPE_1__ args ; 
 int bpf_load_btf (int /*<<< orphan*/ *,unsigned int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_btf_info*,int*) ; 
 char* btf_log_buf ; 
 int /*<<< orphan*/ * btf_raw_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct btf_get_info_test* get_info_tests ; 
 int /*<<< orphan*/  hdr_tmpl ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (struct bpf_btf_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_to_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_big_btf_info(unsigned int test_num)
{
	const struct btf_get_info_test *test = &get_info_tests[test_num - 1];
	uint8_t *raw_btf = NULL, *user_btf = NULL;
	unsigned int raw_btf_size;
	struct {
		struct bpf_btf_info info;
		uint64_t garbage;
	} info_garbage;
	struct bpf_btf_info *info;
	int btf_fd = -1, err;
	uint32_t info_len;

	raw_btf = btf_raw_create(&hdr_tmpl,
				 test->raw_types,
				 test->str_sec,
				 test->str_sec_size,
				 &raw_btf_size, NULL);

	if (!raw_btf)
		return -1;

	*btf_log_buf = '\0';

	user_btf = malloc(raw_btf_size);
	if (CHECK(!user_btf, "!user_btf")) {
		err = -1;
		goto done;
	}

	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      args.always_log);
	if (CHECK(btf_fd == -1, "errno:%d", errno)) {
		err = -1;
		goto done;
	}

	/*
	 * GET_INFO should error out if the userspace info
	 * has non zero tailing bytes.
	 */
	info = &info_garbage.info;
	memset(info, 0, sizeof(*info));
	info_garbage.garbage = 0xdeadbeef;
	info_len = sizeof(info_garbage);
	info->btf = ptr_to_u64(user_btf);
	info->btf_size = raw_btf_size;

	err = bpf_obj_get_info_by_fd(btf_fd, info, &info_len);
	if (CHECK(!err, "!err")) {
		err = -1;
		goto done;
	}

	/*
	 * GET_INFO should succeed even info_len is larger than
	 * the kernel supported as long as tailing bytes are zero.
	 * The kernel supported info len should also be returned
	 * to userspace.
	 */
	info_garbage.garbage = 0;
	err = bpf_obj_get_info_by_fd(btf_fd, info, &info_len);
	if (CHECK(err || info_len != sizeof(*info),
		  "err:%d errno:%d info_len:%u sizeof(*info):%lu",
		  err, errno, info_len, sizeof(*info))) {
		err = -1;
		goto done;
	}

	fprintf(stderr, "OK");

done:
	if (*btf_log_buf && (err || args.always_log))
		fprintf(stderr, "\n%s", btf_log_buf);

	free(raw_btf);
	free(user_btf);

	if (btf_fd != -1)
		close(btf_fd);

	return err;
}