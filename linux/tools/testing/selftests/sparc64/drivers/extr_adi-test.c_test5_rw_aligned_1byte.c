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
typedef  int /*<<< orphan*/  version ;
typedef  unsigned long off_t ;
typedef  unsigned long loff_t ;

/* Variables and functions */
 int ADI_BLKSZ ; 
 int /*<<< orphan*/  DEBUG_PRINT_L2 (char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  RETURN_FROM_TEST (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TEST_STEP_FAILURE (unsigned char) ; 
 int* end_addr ; 
 unsigned char random_version () ; 
 int range_count ; 
 int read_adi (int,unsigned char*,int) ; 
 unsigned long seek_adi (int,unsigned long,int /*<<< orphan*/ ) ; 
 int write_adi (int,unsigned char*,int) ; 

__attribute__((used)) static int test5_rw_aligned_1byte(int fd)
{
	/* somewhat arbitrarily chosen address */
	unsigned long paddr =
		(end_addr[range_count - 1] - 0xF000) & ~(ADI_BLKSZ - 1);
	unsigned char version, expected_version;
	loff_t offset;
	off_t oret;
	int ret;

	offset = paddr / ADI_BLKSZ;
	version = expected_version = random_version();

	oret = seek_adi(fd, offset, SEEK_SET);
	if (oret != offset) {
		ret = -1;
		TEST_STEP_FAILURE(ret);
	}

	ret = write_adi(fd, &version, sizeof(version));
	if (ret != sizeof(version))
		TEST_STEP_FAILURE(ret);

	oret = seek_adi(fd, offset, SEEK_SET);
	if (oret != offset) {
		ret = -1;
		TEST_STEP_FAILURE(ret);
	}

	ret = read_adi(fd, &version, sizeof(version));
	if (ret != sizeof(version))
		TEST_STEP_FAILURE(ret);

	if (expected_version != version) {
		DEBUG_PRINT_L2("\tExpected version %d but read version %d\n",
			       expected_version, version);
		TEST_STEP_FAILURE(-expected_version);
	}

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
}