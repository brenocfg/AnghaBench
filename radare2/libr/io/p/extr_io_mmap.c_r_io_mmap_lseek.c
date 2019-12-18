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
typedef  int ut64 ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  RIOMMapFileObj ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int r_io_mmap_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static ut64 r_io_mmap_lseek(RIO *io, RIODesc *fd, ut64 offset, int whence) {
	RIOMMapFileObj *mmo;
	if (!fd || !fd->data) {
		return -1;
	}
	mmo = fd->data;
	return r_io_mmap_seek (io, mmo, offset, whence);
}