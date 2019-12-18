#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct address_space {TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int dax_writeback_mapping_range (struct address_space*,int /*<<< orphan*/ ,struct writeback_control*) ; 

__attribute__((used)) static int
ext2_dax_writepages(struct address_space *mapping, struct writeback_control *wbc)
{
	return dax_writeback_mapping_range(mapping,
			mapping->host->i_sb->s_bdev, wbc);
}