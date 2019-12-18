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
struct btrfs_stripe {int dummy; } ;
struct btrfs_chunk {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long btrfs_chunk_item_size(int num_stripes)
{
    return sizeof(struct btrfs_chunk) +
           sizeof(struct btrfs_stripe) * (num_stripes - 1);
}