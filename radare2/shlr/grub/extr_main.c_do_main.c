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
struct grub_fs {scalar_t__ (* open ) (struct grub_file*,char*) ;scalar_t__ (* read ) (struct grub_file*,char*,int /*<<< orphan*/ ) ;scalar_t__ (* dir ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (struct grub_file*) ;} ;
struct grub_file {int /*<<< orphan*/  device; int /*<<< orphan*/  size; } ;
typedef  scalar_t__ grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFILE ; 
 int /*<<< orphan*/  dirhook ; 
 struct grub_fs grub_ext2_fs ; 
 int /*<<< orphan*/  grub_print_error () ; 
 struct grub_file* openimage (struct grub_fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (struct grub_file*,char*) ; 
 scalar_t__ stub2 (struct grub_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct grub_file*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

int do_main() {
	struct grub_file *file;
	struct grub_fs *e2;
	grub_err_t err;

	e2 = &grub_ext2_fs;
	file = openimage (e2, IMGFILE);
	if (file == NULL) {
		printf ("oops\n");
		return 0;
	}

	err = e2->open (file, "/test");
	if (err == 0) {
		char buf[1024];
		err = e2->read (file, buf, file->size);
//file->read_hook (2, 0, 0);
		write (1, buf, file->size);
		e2->close (file);

		// Root directory list
		err = e2->dir (file->device, "/", dirhook, 0);
		if (err != 0)
			grub_print_error ();
	} else {
		grub_print_error ();
		printf ("error is : %d\n", err);
		return 0;
	}
	return 1;
}