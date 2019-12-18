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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT_L2 (char*) ; 
 scalar_t__ EINVAL ; 
 int OFFSET_ADD ; 
 int OFFSET_SUBTRACT ; 
 int /*<<< orphan*/  RETURN_FROM_TEST (int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TEST_STEP_FAILURE (int) ; 
 scalar_t__ errno ; 
 int seek_adi (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test4_lseek(int fd)
{
#define	OFFSET_ADD	(0x100)
#define OFFSET_SUBTRACT	(0xFFFFFFF000000000)

	off_t offset_out, offset_in;
	int ret;


	offset_in = 0x123456789abcdef0;
	offset_out = seek_adi(fd, offset_in, SEEK_SET);
	if (offset_out != offset_in) {
		ret = -1;
		TEST_STEP_FAILURE(ret);
	}

	/* seek to the current offset.  this should return EINVAL */
	offset_out = seek_adi(fd, offset_in, SEEK_SET);
	if (offset_out < 0 && errno == EINVAL)
		DEBUG_PRINT_L2(
			"\tSEEK_SET failed as designed. Not an error\n");
	else {
		ret = -2;
		TEST_STEP_FAILURE(ret);
	}

	offset_out = seek_adi(fd, 0, SEEK_CUR);
	if (offset_out != offset_in) {
		ret = -3;
		TEST_STEP_FAILURE(ret);
	}

	offset_out = seek_adi(fd, OFFSET_ADD, SEEK_CUR);
	if (offset_out != (offset_in + OFFSET_ADD)) {
		ret = -4;
		TEST_STEP_FAILURE(ret);
	}

	offset_out = seek_adi(fd, OFFSET_SUBTRACT, SEEK_CUR);
	if (offset_out != (offset_in + OFFSET_ADD + OFFSET_SUBTRACT)) {
		ret = -5;
		TEST_STEP_FAILURE(ret);
	}

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
}