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
struct block_device {struct block_device* bd_contains; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 void* read_dev_sector (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned char *scsi_bios_ptable(struct block_device *dev)
{
	unsigned char *res = kmalloc(66, GFP_KERNEL);
	if (res) {
		struct block_device *bdev = dev->bd_contains;
		Sector sect;
		void *data = read_dev_sector(bdev, 0, &sect);
		if (data) {
			memcpy(res, data + 0x1be, 66);
			put_dev_sector(sect);
		} else {
			kfree(res);
			res = NULL;
		}
	}
	return res;
}