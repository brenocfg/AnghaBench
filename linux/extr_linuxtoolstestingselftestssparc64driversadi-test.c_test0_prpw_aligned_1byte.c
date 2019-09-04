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
typedef  unsigned long loff_t ;

/* Variables and functions */
 int ADI_BLKSZ ; 
 int /*<<< orphan*/  DEBUG_PRINT_L2 (char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  RETURN_FROM_TEST (int) ; 
 int /*<<< orphan*/  TEST_STEP_FAILURE (unsigned char) ; 
 int* end_addr ; 
 int pread_adi (int,unsigned char*,int,unsigned long) ; 
 int pwrite_adi (int,unsigned char*,int,unsigned long) ; 
 unsigned char random_version () ; 
 int range_count ; 

__attribute__((used)) static int test0_prpw_aligned_1byte(int fd)
{
	/* somewhat arbitrarily chosen address */
	unsigned long paddr =
		(end_addr[range_count - 1] - 0x1000) & ~(ADI_BLKSZ - 1);
	unsigned char version[1], expected_version;
	loff_t offset;
	int ret;

	version[0] = random_version();
	expected_version = version[0];

	offset = paddr / ADI_BLKSZ;

	ret = pwrite_adi(fd, version, sizeof(version), offset);
	if (ret != sizeof(version))
		TEST_STEP_FAILURE(ret);

	ret = pread_adi(fd, version, sizeof(version), offset);
	if (ret != sizeof(version))
		TEST_STEP_FAILURE(ret);

	if (expected_version != version[0]) {
		DEBUG_PRINT_L2("\tExpected version %d but read version %d\n",
			       expected_version, version[0]);
		TEST_STEP_FAILURE(-expected_version);
	}

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
}