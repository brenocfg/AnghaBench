#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btf_type {int dummy; } ;
struct btf_header {int str_off; int str_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  str_sec; int /*<<< orphan*/  raw_types; } ;
struct TYPE_3__ {int /*<<< orphan*/  str_sec_size; int /*<<< orphan*/  str_sec; int /*<<< orphan*/  raw_types; } ;
struct btf_dedup_test {char* descr; int /*<<< orphan*/  opts; TYPE_2__ expect; TYPE_1__ input; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ CHECK (int,char*,...) ; 
 int IS_ERR (struct btf*) ; 
 int PTR_ERR (struct btf*) ; 
 int btf__dedup (struct btf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btf__free (struct btf*) ; 
 int btf__get_nr_types (struct btf*) ; 
 void* btf__get_raw_data (struct btf*,int*) ; 
 struct btf* btf__new (int /*<<< orphan*/ *,unsigned int) ; 
 struct btf_type* btf__type_by_id (struct btf*,int) ; 
 void* btf_raw_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,char const**) ; 
 int btf_type_size (struct btf_type const*) ; 
 struct btf_dedup_test* dedup_tests ; 
 int /*<<< orphan*/  dump_btf_strings (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hdr_tmpl ; 
 int memcmp (void*,void*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int do_test_dedup(unsigned int test_num)
{
	const struct btf_dedup_test *test = &dedup_tests[test_num - 1];
	__u32 test_nr_types, expect_nr_types, test_btf_size, expect_btf_size;
	const struct btf_header *test_hdr, *expect_hdr;
	struct btf *test_btf = NULL, *expect_btf = NULL;
	const void *test_btf_data, *expect_btf_data;
	const char *ret_test_next_str, *ret_expect_next_str;
	const char *test_strs, *expect_strs;
	const char *test_str_cur, *test_str_end;
	const char *expect_str_cur, *expect_str_end;
	unsigned int raw_btf_size;
	void *raw_btf;
	int err = 0, i;

	fprintf(stderr, "BTF dedup test[%u] (%s):", test_num, test->descr);

	raw_btf = btf_raw_create(&hdr_tmpl, test->input.raw_types,
				 test->input.str_sec, test->input.str_sec_size,
				 &raw_btf_size, &ret_test_next_str);
	if (!raw_btf)
		return -1;
	test_btf = btf__new((__u8 *)raw_btf, raw_btf_size);
	free(raw_btf);
	if (CHECK(IS_ERR(test_btf), "invalid test_btf errno:%ld",
		  PTR_ERR(test_btf))) {
		err = -1;
		goto done;
	}

	raw_btf = btf_raw_create(&hdr_tmpl, test->expect.raw_types,
				 test->expect.str_sec,
				 test->expect.str_sec_size,
				 &raw_btf_size, &ret_expect_next_str);
	if (!raw_btf)
		return -1;
	expect_btf = btf__new((__u8 *)raw_btf, raw_btf_size);
	free(raw_btf);
	if (CHECK(IS_ERR(expect_btf), "invalid expect_btf errno:%ld",
		  PTR_ERR(expect_btf))) {
		err = -1;
		goto done;
	}

	err = btf__dedup(test_btf, NULL, &test->opts);
	if (CHECK(err, "btf_dedup failed errno:%d", err)) {
		err = -1;
		goto done;
	}

	test_btf_data = btf__get_raw_data(test_btf, &test_btf_size);
	expect_btf_data = btf__get_raw_data(expect_btf, &expect_btf_size);
	if (CHECK(test_btf_size != expect_btf_size,
		  "test_btf_size:%u != expect_btf_size:%u",
		  test_btf_size, expect_btf_size)) {
		err = -1;
		goto done;
	}

	test_hdr = test_btf_data;
	test_strs = test_btf_data + sizeof(*test_hdr) + test_hdr->str_off;
	expect_hdr = expect_btf_data;
	expect_strs = expect_btf_data + sizeof(*test_hdr) + expect_hdr->str_off;
	if (CHECK(test_hdr->str_len != expect_hdr->str_len,
		  "test_hdr->str_len:%u != expect_hdr->str_len:%u",
		  test_hdr->str_len, expect_hdr->str_len)) {
		fprintf(stderr, "\ntest strings:\n");
		dump_btf_strings(test_strs, test_hdr->str_len);
		fprintf(stderr, "\nexpected strings:\n");
		dump_btf_strings(expect_strs, expect_hdr->str_len);
		err = -1;
		goto done;
	}

	test_str_cur = test_strs;
	test_str_end = test_strs + test_hdr->str_len;
	expect_str_cur = expect_strs;
	expect_str_end = expect_strs + expect_hdr->str_len;
	while (test_str_cur < test_str_end && expect_str_cur < expect_str_end) {
		size_t test_len, expect_len;

		test_len = strlen(test_str_cur);
		expect_len = strlen(expect_str_cur);
		if (CHECK(test_len != expect_len,
			  "test_len:%zu != expect_len:%zu "
			  "(test_str:%s, expect_str:%s)",
			  test_len, expect_len, test_str_cur, expect_str_cur)) {
			err = -1;
			goto done;
		}
		if (CHECK(strcmp(test_str_cur, expect_str_cur),
			  "test_str:%s != expect_str:%s",
			  test_str_cur, expect_str_cur)) {
			err = -1;
			goto done;
		}
		test_str_cur += test_len + 1;
		expect_str_cur += expect_len + 1;
	}
	if (CHECK(test_str_cur != test_str_end,
		  "test_str_cur:%p != test_str_end:%p",
		  test_str_cur, test_str_end)) {
		err = -1;
		goto done;
	}

	test_nr_types = btf__get_nr_types(test_btf);
	expect_nr_types = btf__get_nr_types(expect_btf);
	if (CHECK(test_nr_types != expect_nr_types,
		  "test_nr_types:%u != expect_nr_types:%u",
		  test_nr_types, expect_nr_types)) {
		err = -1;
		goto done;
	}

	for (i = 1; i <= test_nr_types; i++) {
		const struct btf_type *test_type, *expect_type;
		int test_size, expect_size;

		test_type = btf__type_by_id(test_btf, i);
		expect_type = btf__type_by_id(expect_btf, i);
		test_size = btf_type_size(test_type);
		expect_size = btf_type_size(expect_type);

		if (CHECK(test_size != expect_size,
			  "type #%d: test_size:%d != expect_size:%u",
			  i, test_size, expect_size)) {
			err = -1;
			goto done;
		}
		if (CHECK(memcmp((void *)test_type,
				 (void *)expect_type,
				 test_size),
			  "type #%d: contents differ", i)) {
			err = -1;
			goto done;
		}
	}

done:
	if (!err)
		fprintf(stderr, "OK");
	if (!IS_ERR(test_btf))
		btf__free(test_btf);
	if (!IS_ERR(expect_btf))
		btf__free(expect_btf);

	return err;
}