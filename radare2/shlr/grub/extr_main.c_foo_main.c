#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  device; TYPE_1__* fs; scalar_t__ size; } ;
struct TYPE_9__ {TYPE_3__* file; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dir ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (TYPE_3__*) ;int /*<<< orphan*/  (* read ) (TYPE_3__*,char*,scalar_t__) ;int /*<<< orphan*/  (* open ) (TYPE_3__*,char*) ;} ;
typedef  TYPE_2__ GrubFS ;

/* Variables and functions */
 int /*<<< orphan*/  dirhook ; 
 int /*<<< orphan*/  grub_ext2_fs ; 
 int /*<<< orphan*/  grubfs_free (TYPE_2__*) ; 
 TYPE_2__* grubfs_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,scalar_t__) ; 

int foo_main() {
	char buf[1024];
	GrubFS *gfs = grubfs_new (&grub_ext2_fs, NULL);
	gfs->file->fs->open (gfs->file, "/test");
	gfs->file->fs->read (gfs->file, buf, gfs->file->size);
printf ("fs = %d\n", (int)gfs->file->size);
	write (1, buf, gfs->file->size);
	gfs->file->fs->close (gfs->file);
	gfs->file->fs->dir (gfs->file->device, "/", dirhook, 0);
	grubfs_free (gfs);
	return 0;
}