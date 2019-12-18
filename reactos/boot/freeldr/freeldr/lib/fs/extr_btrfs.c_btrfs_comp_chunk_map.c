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
struct btrfs_chunk_map_item {scalar_t__ logical; } ;

/* Variables and functions */

__attribute__((used)) static int btrfs_comp_chunk_map(struct btrfs_chunk_map_item *m1,
                                struct btrfs_chunk_map_item *m2)
{
    if (m1->logical > m2->logical)
        return 1;
    if (m1->logical < m2->logical)
        return -1;
    return 0;
}