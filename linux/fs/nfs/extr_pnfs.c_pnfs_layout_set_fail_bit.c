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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_refcount; int /*<<< orphan*/  plh_flags; int /*<<< orphan*/  plh_retry_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_layout_set_fail_bit(struct pnfs_layout_hdr *lo, int fail_bit)
{
	lo->plh_retry_timestamp = jiffies;
	if (!test_and_set_bit(fail_bit, &lo->plh_flags))
		refcount_inc(&lo->plh_refcount);
}