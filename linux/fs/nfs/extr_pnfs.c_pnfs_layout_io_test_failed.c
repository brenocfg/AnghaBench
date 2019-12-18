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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_retry_timestamp; int /*<<< orphan*/  plh_flags; } ;

/* Variables and functions */
 unsigned long PNFS_LAYOUTGET_RETRY_TIMEOUT ; 
 unsigned long jiffies ; 
 int pnfs_iomode_to_fail_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_layout_clear_fail_bit (struct pnfs_layout_hdr*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_in_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static bool
pnfs_layout_io_test_failed(struct pnfs_layout_hdr *lo, u32 iomode)
{
	unsigned long start, end;
	int fail_bit = pnfs_iomode_to_fail_bit(iomode);

	if (test_bit(fail_bit, &lo->plh_flags) == 0)
		return false;
	end = jiffies;
	start = end - PNFS_LAYOUTGET_RETRY_TIMEOUT;
	if (!time_in_range(lo->plh_retry_timestamp, start, end)) {
		/* It is time to retry the failed layoutgets */
		pnfs_layout_clear_fail_bit(lo, fail_bit);
		return false;
	}
	return true;
}