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
struct TYPE_2__ {int rc; int prog_type; int expected_attach_type; } ;
struct sec_name_test {int /*<<< orphan*/  sec_name; TYPE_1__ expected_load; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int libbpf_prog_type_by_name (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  warnx (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_prog_type_by_name(const struct sec_name_test *test)
{
	enum bpf_attach_type expected_attach_type;
	enum bpf_prog_type prog_type;
	int rc;

	rc = libbpf_prog_type_by_name(test->sec_name, &prog_type,
				      &expected_attach_type);

	if (rc != test->expected_load.rc) {
		warnx("prog: unexpected rc=%d for %s", rc, test->sec_name);
		return -1;
	}

	if (rc)
		return 0;

	if (prog_type != test->expected_load.prog_type) {
		warnx("prog: unexpected prog_type=%d for %s", prog_type,
		      test->sec_name);
		return -1;
	}

	if (expected_attach_type != test->expected_load.expected_attach_type) {
		warnx("prog: unexpected expected_attach_type=%d for %s",
		      expected_attach_type, test->sec_name);
		return -1;
	}

	return 0;
}