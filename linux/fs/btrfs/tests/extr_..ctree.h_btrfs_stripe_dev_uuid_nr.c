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
struct btrfs_chunk {int dummy; } ;

/* Variables and functions */
 char* btrfs_stripe_dev_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_stripe_nr (struct btrfs_chunk*,int) ; 

__attribute__((used)) static inline char *btrfs_stripe_dev_uuid_nr(struct btrfs_chunk *c, int nr)
{
	return btrfs_stripe_dev_uuid(btrfs_stripe_nr(c, nr));
}