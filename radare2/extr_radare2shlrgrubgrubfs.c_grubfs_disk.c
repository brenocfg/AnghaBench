#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grub_disk_dev {int dummy; } ;
struct grub_disk {void* data; TYPE_1__* dev; } ;
typedef  struct grub_disk* grub_disk_t ;
struct TYPE_2__ {int /*<<< orphan*/  read; } ;

/* Variables and functions */
 void* empty (int) ; 
 int /*<<< orphan*/  read_foo ; 

grub_disk_t grubfs_disk (void *data) {
	struct grub_disk *disk = empty (sizeof (struct grub_disk));
	disk->dev = empty (sizeof (struct grub_disk_dev));
	disk->dev->read = read_foo; // grub_disk_dev
	disk->data = data;
	return disk;
}