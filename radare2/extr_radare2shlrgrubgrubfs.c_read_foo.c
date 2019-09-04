#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct grub_disk {TYPE_1__* data; } ;
typedef  int const grub_size_t ;
typedef  int grub_err_t ;
typedef  int const grub_disk_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int const) ;} ;
typedef  TYPE_1__ RIOBind ;

/* Variables and functions */
 TYPE_1__* bio ; 
 scalar_t__ delta ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static grub_err_t read_foo (struct grub_disk *disk, grub_disk_addr_t sector, grub_size_t size, char *buf) {
	if (!disk) {
		eprintf ("oops. no disk\n");
		return 1;
	}
	const int blocksize = 512; // TODO unhardcode 512
	RIOBind *iob = disk->data;
	if (bio) {
		iob = bio;
	}
	//printf ("io %p\n", file->root->iob.io);
	return !iob->read_at (iob->io, delta+(blocksize*sector), (ut8*)buf, size*blocksize);
}