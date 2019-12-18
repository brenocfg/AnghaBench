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
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct inode {int dummy; } ;
typedef  int s64 ;
struct TYPE_2__ {int loadaddr; unsigned int execaddr; } ;

/* Variables and functions */
 TYPE_1__* ADFS_I (struct inode*) ; 
 int /*<<< orphan*/  adfs_inode_is_stamped (struct inode*) ; 
 struct timespec64 current_time (struct inode*) ; 
 struct timespec64 ns_to_timespec64 (int) ; 

__attribute__((used)) static void
adfs_adfs2unix_time(struct timespec64 *tv, struct inode *inode)
{
	unsigned int high, low;
	/* 01 Jan 1970 00:00:00 (Unix epoch) as nanoseconds since
	 * 01 Jan 1900 00:00:00 (RISC OS epoch)
	 */
	static const s64 nsec_unix_epoch_diff_risc_os_epoch =
							2208988800000000000LL;
	s64 nsec;

	if (!adfs_inode_is_stamped(inode))
		goto cur_time;

	high = ADFS_I(inode)->loadaddr & 0xFF; /* top 8 bits of timestamp */
	low  = ADFS_I(inode)->execaddr;    /* bottom 32 bits of timestamp */

	/* convert 40-bit centi-seconds to 32-bit seconds
	 * going via nanoseconds to retain precision
	 */
	nsec = (((s64) high << 32) | (s64) low) * 10000000; /* cs to ns */

	/* Files dated pre  01 Jan 1970 00:00:00. */
	if (nsec < nsec_unix_epoch_diff_risc_os_epoch)
		goto too_early;

	/* convert from RISC OS to Unix epoch */
	nsec -= nsec_unix_epoch_diff_risc_os_epoch;

	*tv = ns_to_timespec64(nsec);
	return;

 cur_time:
	*tv = current_time(inode);
	return;

 too_early:
	tv->tv_sec = tv->tv_nsec = 0;
	return;
}