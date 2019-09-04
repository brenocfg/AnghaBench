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

/* Variables and functions */
 unsigned long long do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 void* fake_storep ; 
 unsigned long long sdebug_sector_size ; 
 int /*<<< orphan*/  sdebug_store_sectors ; 

__attribute__((used)) static void *lba2fake_store(unsigned long long lba)
{
	lba = do_div(lba, sdebug_store_sectors);

	return fake_storep + lba * sdebug_sector_size;
}