#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct r_io_t {int off; } ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  rbuf; } ;
typedef  TYPE_1__ Rihex ;
typedef  TYPE_2__ RIODesc ;

/* Variables and functions */
 int r_buf_seek (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ut64 __lseek(struct r_io_t *io, RIODesc *fd, ut64 offset, int whence) {
	Rihex *rih;
	if (!fd || !fd->data) {
		return -1;
	}
	rih = fd->data;
	io->off = r_buf_seek (rih->rbuf, offset, whence);
	return io->off;
}