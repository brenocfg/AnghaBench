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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ POINTER_VALUE ; 
 int TEST_DATA_LEN ; 
 int bpf_prog_test_run (int,int,void*,size_t,int /*<<< orphan*/ *,int*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_admin (int) ; 

__attribute__((used)) static int do_prog_test_run(int fd_prog, bool unpriv, uint32_t expected_val,
			    void *data, size_t size_data)
{
	__u8 tmp[TEST_DATA_LEN << 2];
	__u32 size_tmp = sizeof(tmp);
	uint32_t retval;
	int err;

	if (unpriv)
		set_admin(true);
	err = bpf_prog_test_run(fd_prog, 1, data, size_data,
				tmp, &size_tmp, &retval, NULL);
	if (unpriv)
		set_admin(false);
	if (err && errno != 524/*ENOTSUPP*/ && errno != EPERM) {
		printf("Unexpected bpf_prog_test_run error ");
		return err;
	}
	if (!err && retval != expected_val &&
	    expected_val != POINTER_VALUE) {
		printf("FAIL retval %d != %d ", retval, expected_val);
		return 1;
	}

	return 0;
}