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
struct iomap {int /*<<< orphan*/  dax_dev; int /*<<< orphan*/  bdev; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int __dax_zero_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  iomap_sector (struct iomap*,int) ; 

__attribute__((used)) static int iomap_dax_zero(loff_t pos, unsigned offset, unsigned bytes,
		struct iomap *iomap)
{
	return __dax_zero_page_range(iomap->bdev, iomap->dax_dev,
			iomap_sector(iomap, pos & PAGE_MASK), offset, bytes);
}