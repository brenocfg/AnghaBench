#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grub_fs_t ;
typedef  TYPE_1__* grub_file_t ;
typedef  TYPE_2__* grub_disk_dev_t ;
struct TYPE_7__ {TYPE_2__* dev; struct TYPE_7__* disk; } ;
struct TYPE_6__ {int /*<<< orphan*/  read; } ;
struct TYPE_5__ {int size; void* data; scalar_t__ offset; int /*<<< orphan*/  fs; TYPE_4__* device; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fread (void*,int,int,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_foo ; 

grub_file_t openimage(grub_fs_t fs, const char *str) {
	grub_file_t file = malloc (1024);
	file->device = malloc (1024);
	memset (file->device, 0, 1024);
	file->device->disk = malloc (1024);
	memset (file->device->disk, 0, 1024);
	//file->device->disk->name = "disk0"; //strdup ("disk0");
	file->device->disk->dev = (grub_disk_dev_t)file->device;
	//file->device->disk->dev->read = read_hook; //file->device;
	file->device->disk->dev->read = read_foo; //file->device;
	//file->device->disk->read_hook = read_hook; //read_hook;
	//file->device->read = read_hook;
	//file->read_hook = read_hook;
	//&device; // HACK to avoid segfault
	file->fs = fs;
#if 0
	file->offset = 0;
	file->size = 12190208;
	file->data = malloc (file->size);
	{
		FILE *fd = fopen(IMGFILE, "rb");
		if (fd == NULL) {
			printf ("Cannot open fs image\n");
			return NULL;
		}
		fread (file->data, file->size, 1, fd);
		fclose (fd);
	}
#endif
	return file;
}