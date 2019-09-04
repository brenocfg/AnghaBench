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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_10__ {scalar_t__ off; } ;
struct TYPE_9__ {TYPE_1__* data; } ;
struct TYPE_8__ {int perm; int modified; int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ RIOZipFileObj ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 int R_PERM_W ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ ) ; 
 int r_buf_write_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_io_zip_flush_file (TYPE_1__*) ; 
 int /*<<< orphan*/  r_io_zip_realloc_buf (TYPE_1__*,int) ; 

__attribute__((used)) static int r_io_zip_write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	RIOZipFileObj *zfo;
	int ret = 0;
	if (!fd || !fd->data || !buf) {
		return -1;
	}
	zfo = fd->data;
	if (!(zfo->perm & R_PERM_W)) {
		return -1;
	}
	if (r_buf_tell (zfo->b) + count >= r_buf_size (zfo->b)) {
		r_io_zip_realloc_buf (zfo, count);
	}
	if (r_buf_size (zfo->b) < io->off) {
		io->off = r_buf_size (zfo->b);
	}
	zfo->modified = 1;
	ret = r_buf_write_at (zfo->b, io->off, buf, count);
	// XXX - Implement a flush of some sort, but until then, lets
	// just write through
	r_io_zip_flush_file (zfo);
	return ret;
}