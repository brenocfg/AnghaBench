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
struct btrfs_raid_bio {scalar_t__ faila; scalar_t__ failb; int real_stripes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __raid56_parity_recover (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  finish_rmw (struct btrfs_raid_bio*) ; 

__attribute__((used)) static void validate_rbio_for_rmw(struct btrfs_raid_bio *rbio)
{
	if (rbio->faila >= 0 || rbio->failb >= 0) {
		BUG_ON(rbio->faila == rbio->real_stripes - 1);
		__raid56_parity_recover(rbio);
	} else {
		finish_rmw(rbio);
	}
}