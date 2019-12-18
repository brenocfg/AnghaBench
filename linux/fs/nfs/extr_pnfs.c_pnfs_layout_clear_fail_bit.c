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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_refcount; int /*<<< orphan*/  plh_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_layout_clear_fail_bit(struct pnfs_layout_hdr *lo, int fail_bit)
{
	if (test_and_clear_bit(fail_bit, &lo->plh_flags))
		refcount_dec(&lo->plh_refcount);
}